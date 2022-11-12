#pragma once
#ifndef STATISTICS_H
#define STATISTICS_H

#include "ImGuiLayer.h"
#include "StandardIncludes.h"
#include <string>

class Statistics : public ImGuiLayer {
public:

	double timeElapsed = 0;
	double frameCount = 0;
	float dt = 0.f;

	float boxRotateAngle = 0.f;
	vec3 boxRotateAxis = vec3(0.f, 1.f, 0.f);

	vec3 cameraPosition = vec3(0.f);
	vec3 cameraLookAt = vec3(0.f);

	void OnRender() override {
		ImGui::Begin("Stats");
		ImGui::Text("Framerate: %s", (std::to_string(dt).c_str()));
		ImGui::Text("Frame count: %s", (std::to_string(frameCount).c_str()));
		ImGui::Text("Time elapsed: %s", (std::to_string(timeElapsed).c_str()));
		ImGui::Text("Actual framerate: %s", (std::to_string(frameCount / timeElapsed).c_str()));
		ImGui::Text("Camera Location: %s", glm::to_string(cameraPosition).c_str());
		ImGui::Text("Camera LookAt: %s", glm::to_string(cameraLookAt).c_str());
		ImGui::Text("Camera Forward: %s", glm::to_string(glm::normalize(cameraLookAt - cameraPosition)).c_str());

		ImGui::SliderFloat("Angle", &boxRotateAngle, 0.f, 6.28f);
		ImGui::SliderFloat3("Axis", &boxRotateAxis.x, 0.f, 1.f);

		ImGui::End();

	}
};

#endif // !STATISTICS_H

