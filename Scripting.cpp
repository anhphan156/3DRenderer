#include "Scripting.h"
#include "WindowController.h"
#include "ResourceLoader.h"
#include "Shader.h"
#include "Mesh.h"

void Scripting::Start()
{
	S1FighterScript();
	S1LightScript();
	S2FighterScript();
	S3WaterScript();
}

void Scripting::S2FighterScript()
{
	auto scene2 = ResourceLoader::GetInstance().GetScene(1);
	scene2->m_objects[0].OnUpdate = [this, scene2](float dt) { 
		if (m_MouseVelocity != vec3(0.f)) {
			auto& fighter = scene2->m_objects[0];
			fighter.SetRotation(dot(m_MouseVelocity, m_MouseVelocity) / 15.f, m_MouseVelocity); 
		}
	};
}

void Scripting::S3WaterScript()
{
	auto scene3 = ResourceLoader::GetInstance().GetScene(2);
	scene3->m_postProcessor->OnUpdate = [this, scene3]() {
		scene3->m_postProcessor->GetShader()->SetUniformFloat("u_frequency", m_frequency);
	};
}

void Scripting::S1FighterScript()
{
	auto scene1 = ResourceLoader::GetInstance().GetScene(0);
	scene1->m_objects[0].OnUpdate = [scene1](float dt) { 
		scene1->m_objects[0].SetRotation(glfwGetTime(), vec3(1.f, 0.f, 0.f)); 
	};
}
void Scripting::S1LightScript() {
	auto scene1 = ResourceLoader::GetInstance().GetScene(0);
	scene1->m_lights[0].OnUpdate = [this, scene1](float dt) {
		scene1->m_lights[0].SetSpecularColor(m_S1SpecularColor);
		scene1->m_lights[0].SetSpecularStrength(m_S1SpecularStrength);
		scene1->m_lights[0].SetPosition(scene1->m_lights[0].GetPosition() + m_MouseVelocity * dt);
	};
}
