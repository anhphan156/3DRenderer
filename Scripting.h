#pragma once
#ifndef SCRIPTING_H
#define SCRIPTING_H

#include "StandardIncludes.h"
#include "ResourceLoader.h"
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
	void SetAmplitude(float a) { m_amplitude = a; }
	void SetTint(bool isTint) { m_tintblue = isTint ? 1.f : 0.f; }

	void S1FighterScript();
	void S1LightScript();
	void S2FighterScript();
	void S3WaterScript();

	void OnResetLight();
	void OnWireframeRender(bool, bool);

private:
	shared_ptr<Scene> m_scenes[4];

	float m_S1SpecularStrength;
	vec3 m_S1SpecularColor;
	vec3 m_MouseVelocity;
	float m_frequency;
	float m_amplitude;
	float m_tintblue;
};
#endif
