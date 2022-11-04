#version 330

uniform vec2 u_resolution;
uniform float u_time;

in vec3 v2f_wsNormal;
in vec2 v2f_texCoords;
in vec3 v2f_fragPos;

in vec3 v2f_ro;
in vec3 v2f_hitPos;

float sphereSDF(vec3 p){
	return length(p - vec3(0.f, 0.f, -4.f)) - 2.f;
}

vec3 normal(vec3 p){
	vec2 e = vec2(1e-2, 0.f);

	return normalize(
		sphereSDF(p) - vec3(
			sphereSDF(p - e.xyy),
			sphereSDF(p - e.yxy),
			sphereSDF(p - e.yyx)
		)
	);
}

float rayMarching(vec3 ro, vec3 rd){
	float d0 = 0.f;	

	for(int i = 0; i < 120; i++){
		vec3 p = ro + rd * d0;	
		float d = sphereSDF(p);
		d0 += d;

		if(d < 0.01f || d0 > 200.f) break;
	}

	return d0;
}

float lightingMask(vec3 p, vec3 lightPos){
	vec3 lightVec = lightPos - p;	
	vec3 surfNormal = normal(p);

	float mask = clamp(dot(lightVec, surfNormal), 0.f, 1.f);

	float rayMarchToLight = rayMarching(p + surfNormal * .02f, lightVec);
	if(rayMarchToLight < distance(p + surfNormal * .02f, lightPos)) mask *= .2;

	return mask;
}

void main(){
	vec3 ro = v2f_ro;
	vec3 rd = normalize(v2f_hitPos - ro);

	float d0 = rayMarching(ro, rd);
	vec3 p = ro + rd*d0;

	vec3 lightPos = vec3(0.f, 0.f, 3.f);
	lightPos.xz = vec2(sin(u_time), cos(u_time));

	vec3 color = vec3(lightingMask(p, lightPos) * vec3(.8, .4, .6));
	
	gl_FragColor = vec4(color, 1.f);
}