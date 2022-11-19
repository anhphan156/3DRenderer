#version 330

in vec2 v2f_texCoords;

struct Texture {
	sampler2D sampler1;
};

uniform Texture u_texture;
uniform vec3 u_textColor;

void main(){
	vec4 sampled = vec4(1.f, 1.f, 1.f, texture(u_texture.sampler1, v2f_texCoords).r);
	gl_FragColor = vec4(u_textColor, 1.f) * sampled;	
}