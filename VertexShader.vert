#version 330

in vec3 vertices;
uniform mat4 u_wvp;

void main()
{
	gl_Position = u_wvp * vec4(vertices, 1.f);
}