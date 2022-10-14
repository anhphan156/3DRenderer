#version 330

uniform vec2 u_resolution;
uniform float u_time;

float sphereSDF(vec3 p){
	float sphere = length(p - vec3(2.f, 1.f, 3.f)) - 1.f;

	return min(sphere, p.y);
}

vec3 normal(vec3 p){
	vec2 e = vec2(.1f, 0.f);

	return normalize(
		vec3(
			sphereSDF(p + e.xyy) - sphereSDF(p - e.xyy),
			sphereSDF(p + e.yxy) - sphereSDF(p - e.yxy),
			sphereSDF(p + e.yyx) - sphereSDF(p - e.yyx)
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
	vec2 uv = gl_FragCoord.xy / u_resolution;

	uv.x *= u_resolution.x / u_resolution.y;
	uv *= 2.f;
	uv -= 1.f;

	vec3 ro = vec3(0.f, 1.f, 0.f);
	vec3 rd = normalize(vec3(uv.x, uv.y, 1.f));

	float d0 = rayMarching(ro, rd);
	vec3 p = ro + rd*d0;

	vec3 lightPos = vec3(2.f, 4.f, 3.f);
	lightPos.xz = vec2(sin(u_time), cos(u_time));

	vec3 color = vec3(lightingMask(p, lightPos) * vec3(.8, .4, .6));
//	vec3 color = normal(p);
	
	gl_FragColor = vec4(color, 1.f);
}