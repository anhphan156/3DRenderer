#version 330

uniform samplerCube u_texture;

in vec3 v2f_texCoords;

void main(){
	gl_FragColor = texture(u_texture, v2f_texCoords) * .4;
}