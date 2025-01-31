#pragma once

#include "GLFW/glfw3.h"
#include <vector>
#include <string>
#include <imgui.h>

enum WindowPropertyName
{
	DECORATIONS = GLFW_DECORATED,
	RESIZABLE = GLFW_RESIZABLE,
	TRASPERENT_BACKGROUND = GLFW_TRANSPARENT_FRAMEBUFFER,
};
struct WindowProperty
{
	WindowPropertyName name;
	int value;
};
static ImGuiIO* m_ImGuiIO = nullptr;

class Window
{
public:
	std::string Name = "New Window";
private:
public:
	Window(float posX, float posY,int sizeX, int sizeY, std::string Name);
	~Window();

	static int Init();
	static void OnAppClose();

	void SetProperty(WindowPropertyName property, int value);
	void Create();
	void Destroy();

	inline GLFWwindow* GetWindow() { return m_Window; }
	bool IsShoudWindowClose();

	void EnableVsync();
	void DisableVsync();

	void MakeCurrentContext();

	void BeginRender();
	void EndRender();
	void UpdateViewPort();
	float GetDeltaTime();
private:
	GLFWwindow* m_Window;
	int m_posX, m_posY, m_sizeX, m_sizeY;
};