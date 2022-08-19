#include "Window.h"
#include <GLFW/glfw3.h>

#include "Events/ApplicationEvent.h"
#include "Events/KeyboardEvent.h"
#include "Events/MouseEvent.h"
#include "Logger.h"

namespace OpenGLRenderer
{
	static bool s_GLFWInitialized = false;
	// static void GLFWErrorCallback(int error, const char* description)
	// {
	// 	LOG_ERROR("Glfw Error ({0}): {1}", error, description);
	// }

	Window::Window(WindowData data)
	{
		m_Data = data;
		LOG_INFO("Creating: {0} ({1}, {2}).", m_Data.Title, m_Data.Width, m_Data.Height);

		if (!s_GLFWInitialized)
		{
            glfwWindowHint(GLFW_SAMPLES, 8);
			int c = glfwInit();
			if (!c)
				return;

			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow((int)m_Data.Width, (int)m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);
		if (m_Window == NULL)
		{
			LOG_ERROR("Failed to create GLFW window");
			glfwTerminate();
			return;
		}
		glfwMakeContextCurrent(m_Window);

		int gladStatus = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		if (!gladStatus)
		{
			LOG_ERROR("Failed to initialize Glad");
			glfwTerminate();
		}

		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_MULTISAMPLE);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_FRONT);
        glFrontFace(GL_CCW);

        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		//Set GLFW callbacks
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
		{
			WindowResizeEvent event(width, height);
			WindowData& wd = *(WindowData*)glfwGetWindowUserPointer(window);
			wd.Width = width;
			wd.Height = height;
			wd.Callback(event);
		});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
		{
			WindowCloseEvent event;
			WindowData& wd = *(WindowData*)glfwGetWindowUserPointer(window);
			wd.Callback(event);
		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			WindowData& wd = *(WindowData*)glfwGetWindowUserPointer(window);
			switch (action)
			{
			    case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					wd.Callback(event);
					break;
				}
    			case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					wd.Callback(event);
					break;
				}
	     	    case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					wd.Callback(event);
					break;
				}
			}
		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
		{
			WindowData& wd = *(WindowData*)glfwGetWindowUserPointer(window);
			switch (action)
			{
			case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					wd.Callback(event);
					break;
				}
    			case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					wd.Callback(event);
					break;
				}
			}
		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			MouseScrolledEvent event((float)xOffset, (float)yOffset);
			WindowData& wd = *(WindowData*)glfwGetWindowUserPointer(window);
			wd.Callback(event);
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
		{
			MouseMovedEvent event((float)xPos, (float)yPos);
			WindowData& wd = *(WindowData*)glfwGetWindowUserPointer(window);
			wd.Callback(event);
		});

	}

	void Window::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}

	void Window::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void Window::SetVSync(bool enabled)
	{
		glfwSwapInterval(enabled);
		m_Data.VSync = enabled;
	}

	bool Window::GetVSync()
	{
		return m_Data.VSync;
	}
}
