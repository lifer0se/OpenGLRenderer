#include "Input.h"
#include "Application.h"
#include <GLFW/glfw3.h>

namespace OpenGLRenderer
{
	Input* Input::s_Instance = new Input();

	bool Input::IsKeyPressed(int keycode)
	{
		GLFWwindow* window = Application::GetInstanceNativeWindow();
		auto state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool Input::IsMouseButtonPressed(int button)
	{
		GLFWwindow* window = Application::GetInstanceNativeWindow();
		auto state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}

	glm::vec2 Input::GetMousePosition()
	{
		GLFWwindow* window = Application::GetInstanceNativeWindow();
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		return { xpos, ypos };
	}
}
