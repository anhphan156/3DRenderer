#version 330

uniform sampler2D u_sampler1;
uniform sampler2D u_sampler2;

uniform float u_inverted;
uniform vec3 u_yuv;

in vec2 v2f_texCoords;
in vec3 v2f_color;

void main(){
	vec3 woodTex = texture(u_sampler1, v2f_texCoords).xyz;	
	vec3 emojiTex = texture(u_sampler2, v2f_texCoords).xyz;	

	vec3 col = mix(woodTex, emojiTex, .5f) * v2f_color;

	mat3 to_yuv = mat3(
		.299f, -.14713f, .615f,
		.587f, -.28886f, -.51499f,
		.144f, .436f, -.10001f
	);

	mat3 to_rgb = mat3(
		1.f, 1.f, 1.f,
		0.f, -.39465f, 2.03211f,
		1.13983f, -.58060f, 0.f
	);

	col.rgb = to_yuv * col.rgb;

	col.rgb *= u_yuv;

	col.rgb = to_rgb * col.rgb;

	col.rgb = mix(col.rgb, 1.f - col.rgb, u_inverted);

	gl_FragColor = vec4(col, 1.f);
}