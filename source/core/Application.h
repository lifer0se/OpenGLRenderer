#ifndef APPLICATION_CLASS_H
#define APPLICATION_CLASS_H

#include "ImGuiLayer.h"
#include "Window.h"
#include "Events/ApplicationEvent.h"
#include "Events/MouseEvent.h"
#include "Events/KeyboardEvent.h"
#include "Layer.h"
#include "LayerStack.h"


namespace OpenGLRenderer
{
	class Application
	{
	public:
		Application();
		~Application();

		void Update();
		void OnEvent(Event& event);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		Window& GetWindow() { return *m_Window; };

		static Application& GetInstance() { return *s_Instance; };
		static Window& GetInstanceWindow() { return GetInstance().GetWindow(); }
		static GLFWwindow* GetInstanceNativeWindow() { return GetInstanceWindow().GetNativeWindow(); }

	private:
		bool OnWindowClosed(WindowCloseEvent event);
        bool OnWindowResized(WindowResizeEvent event);

		static Application* s_Instance;
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		LayerStack m_LayerStack;
		bool m_Running = true;
        float m_LastFrameTime = 0.0f;
	};
}

#endif
