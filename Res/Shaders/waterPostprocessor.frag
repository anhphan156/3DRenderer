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
uniform float u_frequency;

in vec2 v2f_texCoords;


void main(){
	vec2 uv = v2f_texCoords;
	uv = v2f_texCoords + sin(v2f_texCoords.x * u_frequency + u_time) * 1.0/30.0;

	vec3 sceneColor = texture(u_textures.sampler0, uv).xyz;

	gl_FragColor = vec4(sceneColor, 1.0);

}