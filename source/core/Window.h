#ifndef WINDOW_CLASS_H
#define WINDOW_CLASS_H

#include "Events/Event.h"
#include "glad/glad.h"
#include <GLFW/glfw3.h>

namespace OpenGLRenderer
{
	using EventCallback = std::function<void(Event&)>;

	struct WindowData
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;
		bool VSync;
		EventCallback Callback;

		WindowData(const std::string& title = "Window", unsigned int width = 1280, unsigned int height = 720)
			: Title(title), Width(width), Height(height) {}

	};

	class Window
	{
	public:

		Window(WindowData data);
		~Window() {}

		void OnUpdate();
		unsigned int GetWidth() { return m_Data.Width; };
		unsigned int GetHeight() { return m_Data.Height; };

		void SetEventCallback(const EventCallback& callback) { m_Data.Callback = callback; };
		void SetVSync(bool enabled);
		bool GetVSync();
		GLFWwindow* GetNativeWindow() { return m_Window; }

		static Window* Create(const WindowData& data = WindowData()) { return new Window(data); };

	private:
		void Shutdown();
		WindowData m_Data;
		GLFWwindow* m_Window;

		void OnWindowResize(GLFWwindow* window, int width, int height);
		void OnWindowClose(GLFWwindow* window);
		void OnKey(GLFWwindow* window, int key, int scancode, int action, int mods);
		void OnMouseButton(GLFWwindow* window, int button, int action, int mods);
		void OnMouseScroll(GLFWwindow* window, double xOffset, double yOffset);
		void OnMouseMoved(GLFWwindow* window, double xPos, double yPos);
	};
}

#endif
