#version 330

uniform vec2 u_resolution;
uniform float u_time;

in vec3 v2f_wsNormal;
in vec2 v2f_texCoords;
in vec3 v2f_fragPos;

in vec3 v2f_ro;
in vec3 v2f_hitPos;

float smin( float a, float b, float k )
{
    float h = clamp( 0.5+0.5*(b-a)/k, 0.0, 1.0 );
    return mix( b, a, h ) - k*h*(1.0-h);
}

float sphereSDF(vec3 p){
	float sphere1 = length(p - vec3(0.f, 0.3f, sin(u_time))) - .3f;
	float sphere2 = length(p - vec3(0.8f, 0.f, sin(u_time + 3.14f / 2.f))) - .3f;
	float sphere3 = length(p - vec3(0.8f, 0.f, sin(u_time + 3.14f))) - .3f;
	float sphere4 = length(p - vec3(sin(u_time) + 0.f, 0.7f, 0.f)) - .3f;

	return smin(smin(smin(sphere1, sphere2, .5f), sphere3, .5f), sphere4, .7f);
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

	//vec3 lightPos = vec3(0.f, 0.f, 3.f);
	//vec3 color = vec3(lightingMask(p, lightPos) * vec3(.8, .4, .6));

	vec3 color = mix(vec3(1.f), normal(p), lightingMask(p, ro));
	
	// borders
	vec2 uv = v2f_texCoords;

	vec2 band = step(vec2(.05), uv);
	vec2 band2 = step(vec2(.05), .975f - uv);

	float border = band.x * band.y * band2.x * band2.y;

	color = mix(vec3(0.f), color, border);

	gl_FragColor = vec4(color, 1.f);
}