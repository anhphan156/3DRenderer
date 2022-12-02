#version 330

in vec3 vertices;
in vec3 normal;
in vec3 tangent;
in vec3 bitangent;
in vec2 texCoords;
layout (location=10) in mat4 instanceMatrix;

uniform mat4 u_wvp;
uniform mat4 u_modelToWorld;
uniform vec3 u_cameraWorldPos;
uniform bool u_instanceEnabled = false;

out vec3 v2f_wsNormal;
out vec2 v2f_texCoords;
out vec3 v2f_fragPos;
out vec3 v2f_viewDir;
out mat3 v2f_TBN;

void main()
{
	mat4 world = u_modelToWorld;
	if(u_instanceEnabled){
		world *= instanceMatrix;
		gl_Position = u_wvp * instanceMatrix * vec4(vertices, 1.0);
	}else{
		gl_Position = u_wvp * vec4(vertices, 1.f);
	}

	v2f_wsNormal = normalize(mat3(transpose(inverse(world))) * normal);
	v2f_texCoords = texCoords;
	v2f_fragPos = vec3(world * vec4(vertices, 1.f));
	v2f_viewDir = normalize(u_cameraWorldPos - v2f_fragPos);

	vec3 T = normalize(vec3(world * vec4(tangent, 0.0)));
	vec3 N = normalize(vec3(world * vec4(normal, 0.0)));
	vec3 B = cross(N, T);

	v2f_TBN = mat3(T, B, N);
}