#pragma once
#ifndef IMGUI_LAYER_H
#define IMGUI_LAYER_H

#include "Dependencies/imgui/imgui.h"

class ImGuiLayer {
public:
	ImGuiLayer() {}
	virtual ~ImGuiLayer() = default;

	virtual void OnRender() = 0;
};

#endif
