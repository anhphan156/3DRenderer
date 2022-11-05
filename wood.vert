#version 330

in vec3 vertices;
in vec3 color;
in vec2 texCoords;

uniform mat4 u_wvp;

out vec2 v2f_texCoords;
out vec3 v2f_color;

void main()
{
	v2f_texCoords = texCoords;
	v2f_color = color;

	gl_Position = u_wvp * vec4(vertices, 1.f);
}