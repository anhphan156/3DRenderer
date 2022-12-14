#include "ResourceLoader.h"
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"

ResourceLoader::ResourceLoader() {
	m_shaders = make_shared<ShaderMap>();
	m_models = make_shared<ModelMap>();
	m_scene = make_shared<Scene>();
	m_skybox = make_shared<Skybox>();
	m_font = make_shared<Font>();
}

void ResourceLoader::Load() {
	ShaderInit(m_shaders);

	ModelInit("sphere.obj");
	ModelInit("cube.obj");
	ModelInit("skybox.obj");
	ModelInit("window.obj");
	ModelInit("teapot.obj");

	m_font->Create((*m_shaders)["font"].get(), "Arial.ttf", 100);

	m_skybox->Create((*m_shaders)["skybox"].get(), &(*m_models)["skybox.obj"], {
		"Res/Textures/cm1/right.jpg",
		"Res/Textures/cm1/left.jpg",
		"Res/Textures/cm1/top.jpg",
		"Res/Textures/cm1/bottom.jpg",
		"Res/Textures/cm1/front.jpg",
		"Res/Textures/cm1/back.jpg",
	});

	SceneInit(m_scene);
}

void ResourceLoader::ShaderInit(shared_ptr<ShaderMap> shaderMap) const {
	std::ifstream shaderConfig("Res/shaders.config");

	std::string shaderName, shaderFileName, textureName;
	int textureCount;
	float normalEnabled;

	while (shaderConfig) {
		shaderConfig >> shaderName >> shaderFileName >> textureCount >> normalEnabled;

		(*shaderMap)[shaderName] = make_shared<Shader>();
		(*shaderMap)[shaderName]->LoadShaders(("Res/Shaders/" + shaderFileName + ".vert").c_str(), ("Res/Shaders/" + shaderFileName + ".frag").c_str());
		(*shaderMap)[shaderName]->SetNormalEnabled(normalEnabled);

		for (int i = 0; i < textureCount; i++) {
			shaderConfig >> textureName;
			auto texture = make_shared<Texture>();
			texture->LoadTexture("Res/Textures/" + textureName);

			(*shaderMap)[shaderName]->AddTexture(texture);
		}
	}
}

void ResourceLoader::ModelInit(std::string fileName) {
	objl::Loader loader;
	M_ASSERT(loader.LoadFile("Res/Models/" + fileName) == true, "Failed to load mesh");
	(*m_models)[fileName] = loader;

	for (unsigned int i = 0; i < loader.LoadedMeshes.size(); i++) {
		objl::Mesh& mesh = (*m_models)[fileName].LoadedMeshes[i];

		for (unsigned int i = 0; i < (*m_models)[fileName].LoadedIndices.size(); i += 3) {
			unsigned int index = (*m_models)[fileName].LoadedIndices[i];
			auto& p0 = mesh.Vertices[index];
			auto& p1 = mesh.Vertices[index + 1];
			auto& p2 = mesh.Vertices[index + 2];

			objl::Vector3 e1 = p0.Position - p1.Position;
			objl::Vector3 e2 = p0.Position - p2.Position;
			objl::Vector2 duv1 = p0.TextureCoordinate - p1.TextureCoordinate;
			objl::Vector2 duv2 = p0.TextureCoordinate - p2.TextureCoordinate;

			float f = 1.f / (duv1.X * duv2.Y - duv2.X * duv1.Y);

			objl::Vector3 tangent;
			tangent.X = f * (duv2.Y * e1.X - duv1.Y * e2.X);
			tangent.Y = f * (duv2.Y * e1.Y - duv1.Y * e2.Y);
			tangent.Z = f * (duv2.Y * e1.Z - duv1.Y * e2.Z);

			p0.Tangent = tangent;
			p1.Tangent = tangent;
			p2.Tangent = tangent;
		}
	}

}

void ResourceLoader::SceneInit(shared_ptr<Scene> scene) {
	std::ifstream sceneFile("Res/Scenes/Scene.txt");

	int instance;
	std::string type, name, model, shader, lightType;
	float lightStrength;
	vec3 position, scale;
	glm::vec4 rotation;

	while (sceneFile) { // bug to fix: last line is read twice
		sceneFile >> type;

		if (type == "l") {
			sceneFile >> instance >> name >> model >> shader >> lightType >> lightStrength >>
			position.x >> position.y >> position.z >>
			scale.x >> scale.y >> scale.z >>
			rotation.x >> rotation.y >> rotation.z, rotation.w;

			Mesh mesh;
			mesh.Create((*m_shaders)[shader].get(), &(*m_models)[model], instance);
			mesh.SetPosition(position);
			mesh.SetScale(scale);
			mesh.SetLightStrength(lightStrength);
			scene->m_lights.push_back(mesh);
		}

		if (type == "o" || type == "to") {
			sceneFile >> instance >> name >> model >> shader >> 
			position.x >> position.y >> position.z >> 
			scale.x >> scale.y >> scale.z >>
			rotation.x >> rotation.y >> rotation.z >> rotation.w;

			Mesh mesh;
			mesh.SetName(name);
			mesh.Create((*m_shaders)[shader].get(), &(*m_models)[model], instance);
			mesh.SetPosition(position);
			mesh.SetScale(scale);
			mesh.SetLightMesh(m_scene->m_lights);

			if (type == "o") {
				scene->m_objects.push_back(mesh);
			}
			else if (type == "to") {
				scene->m_transluscentObjects.push_back(mesh);
			}
		}
	}
}