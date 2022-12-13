#pragma once
#ifndef RESOURCE_LOADER_H
#define RESOURCE_LOADER_H

#include "StandardIncludes.h"
#include "Scene.h"
#include "Skybox.h"
#include "Font.h"
#include "Singleton.h"
#include <OBJ_Loader.h>

typedef std::map<std::string, shared_ptr<class Shader>> ShaderMap;
typedef std::map<std::string, shared_ptr<class Texture>> TextureMap;
typedef std::map<std::string, objl::Loader> ModelMap;

class ResourceLoader : public Singleton<ResourceLoader>{
public:
	ResourceLoader() = default;
	virtual ~ResourceLoader() = default;

	void Load();

	ShaderMap& GetShaderMap() { return m_shaders; }
	Scene& GetScene() { return m_scene; }
	Font& GetFont() { return m_font; }
	Skybox& GetSkybox() { return m_skybox; }

private:
	void ShaderInit(ShaderMap& shaderMap) const;
	void ModelInit(std::string fileName);
	void SceneInit();

	ShaderMap m_shaders;
	ModelMap m_models;
	Scene m_scene;
	Skybox m_skybox;
	Font m_font;
};

#endif // !RESOURCE_LOADER_H

