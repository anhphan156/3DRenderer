#version 330

in vec3 vertices;
in vec3 normal;
in vec2 texCoords;

uniform mat4 u_wvp;
uniform mat4 u_modelToWorld;
uniform vec3 u_cameraWorldPos;

out vec3 v2f_wsNormal;
out vec2 v2f_texCoords;
out vec3 v2f_fragPos;
out vec3 v2f_viewDir;

void main()
{
	v2f_wsNormal = normalize(mat3(transpose(inverse(u_modelToWorld))) * normal);
	v2f_texCoords = texCoords;
	v2f_fragPos = vec3(u_modelToWorld * vec4(vertices, 1.f));
	v2f_viewDir = normalize(u_cameraWorldPos - v2f_fragPos);

	gl_Position = u_wvp * vec4(vertices, 1.f);
}