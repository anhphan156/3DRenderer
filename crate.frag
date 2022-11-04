#version 330

uniform vec2 u_resolution;
uniform float u_time;

uniform sampler2D u_sampler1;
uniform sampler2D u_sampler2;
uniform sampler2D u_sampler3;

uniform vec3 u_ambientLight;
uniform vec3 u_lightPos;
uniform vec3 u_lightColor;

in vec3 v2f_wsNormal;
in vec2 v2f_texCoords;
in vec3 v2f_fragPos;

void main(){
	vec3 rockTex = texture(u_sampler1, v2f_texCoords).xyz;	
	vec3 noiseTex = texture(u_sampler2, v2f_texCoords).xyz - vec3(.5f);	
	vec3 paintTex = texture(u_sampler3, v2f_texCoords).xyz;	

	vec3 col = mix(rockTex, vec3(0.f, 0.f, 8.f), paintTex.r);
	col = mix(col, vec3(.9f, .1f, .1f), paintTex.g);
	col = mix(col, vec3(1.f, 0.f, 0.f), noiseTex);

	vec3 lightDir = normalize(u_lightPos - v2f_fragPos);
	vec3 lambertian = dot(v2f_wsNormal, lightDir) * u_lightColor;
	vec3 light = clamp(lambertian + u_ambientLight, 0.f, 1.f);

	gl_FragColor = vec4(col * light, 1.f);
}