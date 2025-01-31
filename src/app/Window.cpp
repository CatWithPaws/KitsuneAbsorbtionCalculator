#include "cmath"
#include "Window.h"

#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_glfw.h"

Window::Window(float posX, float posY, int sizeX, int sizeY, std::string name)
	: m_sizeX(sizeX), m_sizeY(sizeY), Name(name)
{
	int count;
	const GLFWvidmode* screenSize = glfwGetVideoMode(glfwGetPrimaryMonitor());
	m_posX = floor(screenSize->width * posX);
	m_posY = floor(screenSize->height * posY);
}

Window::~Window()
{
}


int Window::Init()
{

	//GLFW Initialization
	if (!glfwInit())
	{
		printf("Cannot init GLFW");
		return -1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//ImGUI initialization
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	m_ImGuiIO = &ImGui::GetIO();;
	
	//Configs
	m_ImGuiIO->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	m_ImGuiIO->ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
	m_ImGuiIO->ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows
	//io.ConfigViewportsNoAutoMerge = true;
	//io.ConfigViewportsNoTaskBarIcon = true;

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsLight();

	// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
	ImGuiStyle& style = ImGui::GetStyle();
	if (m_ImGuiIO->ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}

	return 0;
}

void Window::OnAppClose()
{
}

void Window::SetProperty(WindowPropertyName property, int value)
{
	glfwWindowHint(property, value);
}

void Window::Create()
{
	m_Window = glfwCreateWindow(m_sizeX, m_sizeY, Name.c_str(), NULL,NULL);



	glfwSetWindowPos(m_Window, m_posX, m_posY);
	glfwHideWindow(m_Window);
}

void Window::Destroy()
{
	glfwSetWindowShouldClose(m_Window, GLFW_TRUE);
}

bool Window::IsShoudWindowClose()
{
	return glfwWindowShouldClose(m_Window);
}

void Window::EnableVsync()
{
	glfwSwapInterval(1); // Enable vsync
}

void Window::DisableVsync()
{
	glfwSwapInterval(0); // Disable vsync

}

void Window::MakeCurrentContext()
{
	glfwMakeContextCurrent(m_Window);
}

void Window::BeginRender()
{
	glfwPollEvents();

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	glViewport(0, 0, m_sizeX, m_sizeY);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	ImGuiViewport* viewport = ImGui::GetMainViewport();

	//ImGui::SetNextWindowPos(viewport->WorkPos);
	//ImGui::SetNextWindowSize(viewport->WorkSize);
}

void Window::EndRender()
{
	ImGui::Render();
	int display_w, display_h;

	glfwGetFramebufferSize(m_Window, &display_w, &display_h);
	glViewport(0, 0, display_w, display_h);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


	if (m_ImGuiIO->ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		GLFWwindow* backup_current_context = glfwGetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		glfwMakeContextCurrent(backup_current_context);
	}
	glfwSwapBuffers(m_Window);
}

void Window::UpdateViewPort()
{
	GLFWwindow* backup_current_context = glfwGetCurrentContext();
	ImGui::UpdatePlatformWindows();
	ImGui::RenderPlatformWindowsDefault();
	glfwMakeContextCurrent(backup_current_context);
}

float Window::GetDeltaTime()
{
	return glfwGetTime();
}
