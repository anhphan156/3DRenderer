#version 330

layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 FragNormal;

#define NR_LIGHTS 4

struct Textures {
	sampler2D sampler0;
	sampler2D sampler1;
	sampler2D sampler2;
	sampler2D sampler3;
	sampler2D sampler4;
	sampler2D sampler5;
};

struct Light {
	vec3 position;
	float strength;
	vec3 color;
	vec3 ambientColor;
	vec3 lambertianColor;
	vec3 specularColor;
	float specularConcentration;

	vec3 attenuationFactor;

	vec3 spotlightDirection;
	float spotlightAngle;
	float spotlightFalloff;
};

uniform vec2 u_resolution;
uniform float u_time;

uniform Textures u_textures;
uniform Light u_light[NR_LIGHTS];

in vec3 v2f_wsNormal;
in vec2 v2f_texCoords;
in vec3 v2f_fragPos;
in vec3 v2f_viewDir;
in mat3 v2f_TBN;

void main(){
	FragColor = vec4(vec3(.8, .6, .6), .5f);
	FragNormal = vec4(v2f_wsNormal, 1.0);
}