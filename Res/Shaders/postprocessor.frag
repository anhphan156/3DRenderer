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

const float offset = 1.0 / 700.0;

void main(){
	vec3 col = vec3(0.0);
	vec2 uv = v2f_texCoords;
	//uv.y = v2f_texCoords.y + sin(v2f_texCoords.x * 5.0 + u_time) * 1.0/30.0;
	//uv *= .95;

	vec3 sceneColor = texture(u_textures.sampler0, uv).xyz;
	vec3 sceneNormal = texture(u_textures.sampler1, uv).xyz;
	vec3 grayscale = vec3(sceneColor.r * .2126 + sceneColor.g * .7152 + sceneColor.b * .0722);

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

	float edge[9] = float[](
		1, 1, 1,
		1,-8, 1,
		1, 1, 1
	);

	float blur[9] = float[] (
		1.0 / 8.0, 2.0 / 8.0, 1.0 / 8.0,	
		2.0 / 8.0, 4.0 / 8.0, 2.0 / 8.0,	
		1.0 / 8.0, 2.0 / 8.0, 1.0 / 8.0	
	);

	float sharpen[9] = float[] (
		-1, -1, -1,
		-1,  9, -1,
		-1, -1, -1
	);

	vec3 sampleTex[9];
	for(int i = 0; i < 9; i++) sampleTex[i] = texture(u_textures.sampler0, uv + offsets[i]).xyz;
	for(int i = 0; i < 9; i++) col += sampleTex[i] * edge[i];

	vec3 lineColor = mix(vec3(1.0, 0.0, 0.0), vec3(0.0, 0.0, 1.0), sceneNormal) * 5.0;
	col = mix(sceneColor, lineColor, col);

	gl_FragColor = vec4(sceneColor, 1.0);

}