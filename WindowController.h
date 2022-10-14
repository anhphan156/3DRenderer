#pragma once
#ifndef WINDOW_CONTROLLER_H
#define WINDOW_CONTROLLER_H

#include "StandardIncludes.h"
#include "Singleton.h"

class WindowController : public Singleton<WindowController> {
public:
	WindowController();
	virtual ~WindowController();

	GLFWwindow* GetWindow() { if (m_window == nullptr) { NewWindow(); } return m_window; }

	void NewWindow();

	struct Resolution GetResolution();
private:
	GLFWwindow* m_window;
};

#endif
