#pragma once
#ifndef SCRIPTING_H
#define SCRIPTING_H

#include "StandardIncludes.h"
#include "Singleton.h"
#include "Scene.h"

class Scripting :public Singleton<Scripting>{
public:
	Scripting() = default;
	virtual ~Scripting() = default;

	void Start();

	void S1SetSpecularValues(vec3 color, float strength) { m_S1SpecularColor = color; m_S1SpecularStrength = strength; };
	void SetMouseVelocity(vec3 v) { m_MouseVelocity = v; }
	void SetFrequency(float f) { m_frequency = f; }

	void S1FighterScript();
	void S1LightScript();
	void S2FighterScript();
	void S3WaterScript();

private:
	shared_ptr<Scene> m_scenes[4];

	float m_S1SpecularStrength;
	vec3 m_S1SpecularColor;
	vec3 m_MouseVelocity;
	float m_frequency;
};

#endif
