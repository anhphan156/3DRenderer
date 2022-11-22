#version 330

struct Textures {
	sampler2D sampler0;
	sampler2D sampler1;
	sampler2D sampler2;
	sampler2D sampler3;
	sampler2D sampler4;
	sampler2D sampler5;
};

uniform vec2 u_resolution;
uniform float u_time;

uniform Textures u_textures;

in vec2 v2f_texCoords;
in vec3 v2f_fragPos;

void main(){
	vec3 albedo = texture(u_textures.sampler0, v2f_texCoords).xyz;
	gl_FragColor = vec4(albedo * abs(v2f_fragPos), 1.f);
}