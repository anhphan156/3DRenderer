#version 330

in vec3 vertices;
in vec3 normal;
in vec3 tangent;
in vec3 bitangent;
in vec2 texCoords;

uniform mat4 u_wvp;
uniform mat4 u_modelToWorld;
uniform vec3 u_cameraWorldPos;

out vec3 v2f_wsNormal;
out vec2 v2f_texCoords;
out vec3 v2f_fragPos;
out vec3 v2f_viewDir;
out mat3 v2f_TBN;

void main()
{
	v2f_wsNormal = normalize(mat3(transpose(inverse(u_modelToWorld))) * normal);
	v2f_texCoords = texCoords;
	v2f_fragPos = vec3(u_modelToWorld * vec4(vertices, 1.f));
	v2f_viewDir = normalize(u_cameraWorldPos - v2f_fragPos);

	vec3 T = normalize(vec3(u_modelToWorld * vec4(tangent, 0.0)));
	vec3 N = v2f_wsNormal;
	vec3 B = cross(N, T);

	v2f_TBN = mat3(T, B, N);

	gl_Position = u_wvp * vec4(vertices, 1.f);
}