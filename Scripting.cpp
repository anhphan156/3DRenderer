#include "Scripting.h"
#include "ResourceLoader.h"
#include "Mesh.h"

void Scripting::Start()
{
	S1FighterScript();
	S1LightScript();
}

void Scripting::S1FighterScript()
{
	auto scene1 = ResourceLoader::GetInstance().GetScene(1);
	scene1->m_objects[0].OnUpdate = [scene1](float dt) { 
		scene1->m_objects[0].SetRotation(glfwGetTime(), vec3(1.f, 0.f, 0.f)); 
	};

}
void Scripting::S1LightScript() {
	auto scene1 = ResourceLoader::GetInstance().GetScene(1);
	scene1->m_lights[0].OnUpdate = [this, scene1](float dt) {
		scene1->m_lights[0].SetSpecularColor(m_S1SpecularColor);
		scene1->m_lights[0].SetSpecularStrength(m_S1SpecularStrength);
	};
}
