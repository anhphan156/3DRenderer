#version 330

in vec3 vertices;
in vec3 normal;
in vec2 texCoords;

uniform mat4 u_wvp;

out vec3 v2f_normal;
out vec2 v2f_texCoords;

void main()
{
	v2f_normal = normal;
	v2f_texCoords = texCoords;

	gl_Position = u_wvp * vec4(vertices, 1.f);
}