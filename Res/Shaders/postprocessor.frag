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

const float offset = 1.0 / 300.0;

void main(){
	vec3 col = vec3(0.0);

	vec2 offsets[9] = vec2[](
		vec2(-offset, offset), // top left
		vec2(0, offset), // top center
		vec2(offset, offset), // top right
		vec2(-offset, 0), // center left
		vec2(0, 0), // center center
		vec2(offset, 0), // center right
		vec2(-offset, -offset), // bottom left
		vec2(0, -offset), // bottom center
		vec2(offset, -offset) // bottom right
	);

	float kernel[9] = float[](
		1, 1, 1,
		1,-8, 1,
		1, 1, 1
	);

	vec3 sampleTex[9];
	for(int i = 0; i < 9; i++) sampleTex[i] = texture(u_textures.sampler0, v2f_texCoords + offsets[i]).xyz;
	for(int i = 0; i < 9; i++) col += sampleTex[i] * kernel[i];

	col = mix(texture(u_textures.sampler0, v2f_texCoords).xyz, vec3(.3, .4, .8), col);

	gl_FragColor = vec4(col, 1.0);
}