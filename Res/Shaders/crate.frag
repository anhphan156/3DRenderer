#version 330

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
	vec3 albedoMap = texture(u_textures.sampler0, v2f_texCoords).xyz;	
	vec3 specularMap = texture(u_textures.sampler1, v2f_texCoords).xyz;	
	vec3 normalMap = texture(u_textures.sampler2, v2f_texCoords).xyz;	

	normalMap = normalMap * 2.f - 1.f;
	vec3 normal = normalize(v2f_TBN * normalMap);

	vec3 spotlights = vec3(0.f);

	for(int i = 0; i < NR_LIGHTS; i++){
		// distance from light
		vec3 lightDir = normalize(u_light[i].position - v2f_fragPos);
		float dist = length(u_light[i].position - v2f_fragPos);
		float lum = 1.f / (u_light[i].attenuationFactor.x * pow(dist, 2.f) + u_light[i].attenuationFactor.y * dist + u_light[i].attenuationFactor.z);

		// spot light angle
		float a = cos(u_light[i].spotlightAngle);
		float d = dot(normalize(u_light[i].spotlightDirection), -lightDir);
		lum *= 1.f - pow(clamp(a / d, 0.f, 1.f), u_light[i].spotlightFalloff);

		// ambient
		vec3 ambient = clamp(u_light[i].ambientColor * albedoMap * lum, vec3(0.f), vec3(1.f));

		// lambertian
		vec3 lambertian = dot(normal, lightDir) * u_light[i].lambertianColor * 2.f * albedoMap * lum;

		// specular
		vec3 reflection = reflect(-lightDir, normal);
		vec3 specular = pow(max(0.f, dot(reflection, v2f_viewDir)), u_light[i].specularConcentration) * u_light[i].specularColor * specularMap * lum;

		spotlights += mix(clamp(lambertian + ambient + specular, 0.f, 1.f), ambient / NR_LIGHTS, step(0.f, a - d));
		//spotlights += clamp(lambertian + ambient + specular, 0.f, 1.f);
	}

	gl_FragColor = vec4(spotlights, 1.f);
}