#version 330

in vec3 vertices;
in vec2 texCoords;

out vec2 v2f_texCoords;

void main()
{
	v2f_texCoords = texCoords;
	gl_Position = vec4(vertices.xy, 0.0, 1.f);
}