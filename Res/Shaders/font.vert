#version 330

in vec4 vertices;
uniform mat4 u_projection;

out vec2 v2f_texCoords;

void main() {
	gl_Position = u_projection * vec4(vertices.xy, 0.f, 1.f);
	v2f_texCoords = vertices.zw;
}