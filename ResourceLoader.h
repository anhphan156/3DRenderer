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
	ResourceLoader();
	virtual ~ResourceLoader() = default;

	void Load();

	shared_ptr<ShaderMap> GetShaderMap() { return m_shaders; }
	shared_ptr<Scene> GetScene(int index) { return m_scenes[index]; }
	shared_ptr<Font> GetFont() { return m_font; }

	void Cleanup();

private:
	void ShaderInit(shared_ptr<ShaderMap> shaderMap) const;
	void ModelInit(std::string fileName);
	void SceneInit(shared_ptr<Scene> scene, char*);

	shared_ptr<ShaderMap> m_shaders;
	shared_ptr<ModelMap> m_models;
	shared_ptr<Skybox> m_skybox;
	std::map<std::string, shared_ptr<PostProcessor>> m_postProcessors;
	shared_ptr<Font> m_font;
	shared_ptr<Scene> m_scenes[4];
};

#endif // !RESOURCE_LOADER_H

