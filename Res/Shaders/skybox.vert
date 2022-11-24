#version 330

in vec3 vertices;
uniform mat4 u_pv;

out vec3 v2f_texCoords;

void main()
{
	v2f_texCoords = vertices;
	gl_Position = u_pv * vec4(vertices, 1.f);
}