#version 330

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
};

uniform vec2 u_resolution;
uniform float u_time;

uniform Textures u_textures;
uniform Light u_light;

in vec3 v2f_wsNormal;
in vec2 v2f_texCoords;
in vec3 v2f_fragPos;
in vec3 v2f_viewDir;

void main(){
	vec3 wood = texture(u_textures.sampler0, v2f_texCoords).xyz;	
	vec3 frame = texture(u_textures.sampler1, v2f_texCoords).xyz;	

	// ambient
	vec3 ambient = u_light.ambientColor * wood;

	// lambertian
	vec3 lightDir = normalize(u_light.position - v2f_fragPos);
	vec3 lambertian = dot(v2f_wsNormal, lightDir) * u_light.lambertianColor * wood;

	// specular
	vec3 reflection = reflect(-lightDir, v2f_wsNormal);
	vec3 specular = pow(max(0.f, dot(reflection, v2f_viewDir)), u_light.specularConcentration) * u_light.specularColor * frame;

	vec3 light = clamp(lambertian + ambient + specular, 0.f, 1.f);

	gl_FragColor = vec4(light, 1.f);
}