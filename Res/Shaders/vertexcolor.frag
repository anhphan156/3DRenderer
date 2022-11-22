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
	gl_FragColor = vec4(vec3(1.f), 1.f);
}