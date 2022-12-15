#include "Scripting.h"
#include "WindowController.h"
#include "ResourceLoader.h"
#include "Shader.h"
#include "Mesh.h"

void Scripting::AttachScripts()
{
	S1FighterScript();
	S1LightScript();
	S2FighterScript();
	S3WaterScript();
	S4CameraScript();
}

void Scripting::S2FighterScript()
{
	auto scene2 = ResourceLoader::GetInstance().GetScene(1);
	scene2->m_objects[0].OnUpdate = [this, scene2](float dt) { 
		if (m_MouseVelocity != vec3(0.f)) {
			auto& fighter = scene2->m_objects[0];
			if(m_translate)
				fighter.SetPosition(fighter.GetPosition() + m_MouseVelocity * dt);

			if (m_rotate) {
				fighter.SetRotation(dot(m_MouseVelocity, m_MouseVelocity) * .1f, vec3(-m_MouseVelocity.y, m_MouseVelocity.x, m_MouseVelocity.z));
			}

			if (m_scale) 
				fighter.SetScale(fighter.GetScale() + m_MouseVelocity * dt * .002f);
		}
	};
}

void Scripting::S3WaterScript()
{
	auto scene3 = ResourceLoader::GetInstance().GetScene(2);
	scene3->m_postProcessor->OnUpdate = [this, scene3]() {
		scene3->m_postProcessor->GetShader()->SetUniformFloat("u_frequency", m_frequency);
		scene3->m_postProcessor->GetShader()->SetUniformFloat("u_amplitude", m_amplitude);
		scene3->m_postProcessor->GetShader()->SetUniformFloat("u_tintblue", m_tintblue);
	};
}

void Scripting::S4CameraScript()
{
	auto scene4 = ResourceLoader::GetInstance().GetScene(3);
	scene4->m_camera.OnUpdate = [scene4](float dt) {
		scene4->m_camera.cameraTurn(.0005f, 0.f);
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

void Scripting::OnResetLight() { ResourceLoader::GetInstance().GetScene(0)->m_lights[0].SetPosition(vec3(0.f)); }
void Scripting::OnResetTransform() {
	ResourceLoader::GetInstance().GetScene(1)->m_objects[0].SetPosition(vec3(0.f)); 
	ResourceLoader::GetInstance().GetScene(1)->m_objects[0].SetScale(vec3(.01f)); 
	ResourceLoader::GetInstance().GetScene(1)->m_objects[0].SetRotation(0.f, vec3(1.f)); 
}
void Scripting::OnWireframeRender(bool isActive, bool isGameMode2) { if (isGameMode2) { glPolygonMode(GL_FRONT_AND_BACK, isActive ? GL_LINE : GL_FILL); } }
