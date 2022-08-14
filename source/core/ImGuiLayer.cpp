#include "ImGuiLayer.h"
#include "Application.h"

namespace OpenGLRenderer
{
	ImGuiLayer::ImGuiLayer() {}
	ImGuiLayer::~ImGuiLayer() {}

	void ImGuiLayer::OnAttach()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

		GLFWwindow* w = Application::GetInstanceNativeWindow();
		ImGui_ImplGlfw_InitForOpenGL(w, true);
		ImGui_ImplOpenGL3_Init("#version 410");

		LOG_TRACE("ImGuiLayer::Attached");
	}

	void ImGuiLayer::OnDetach()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();

		LOG_TRACE("ImGuiLayer::Detached");
	}

	void ImGuiLayer::OnEvent(Event &event)
	{
		if (!m_BlockEvents)
			return;

		ImGuiIO& io = ImGui::GetIO();
		event.Handled |= event.IsInCategory(EventCategoryMouse) & io.WantCaptureMouse;
		event.Handled |= event.IsInCategory(EventCategoryKeyboard) & io.WantCaptureKeyboard;
	}

	void ImGuiLayer::Begin()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void ImGuiLayer::End()
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(Application::GetInstanceWindow().GetWidth(), Application::GetInstanceWindow().GetHeight());

		ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

}
