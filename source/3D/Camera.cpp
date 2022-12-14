#include "Camera.h"
#include "Input.h"
#include "Events/KeyboardEvent.h"
#include "Logger.h"
#include "Application.h"

namespace OpenGLRenderer
{
	Camera::Camera(float FOVdeg, float nearPlane, float farPlane)
	{
		m_Name ="Camera";
        m_FOV = FOVdeg;
        m_NearPlane = nearPlane;
        m_FarPlane = farPlane;

        m_Width = Application::GetInstanceWindow().GetWidth();
        m_Height = Application::GetInstanceWindow().GetHeight();

		m_ViewMatrix = glm::lookAt(GetPosition(), GetPosition() + GetForward(), GetUp());
		m_ProjectionMatrix = glm::perspective(glm::radians(m_FOV), (float)m_Width / (float)m_Height, m_NearPlane, m_FarPlane);
		m_CameraMatrix = m_ProjectionMatrix * m_ViewMatrix;

        LOG_INFO("Camera::Setup");
	}

	void Camera::Translate(vec3 offset)
	{
		Actor::Translate(offset);
        CalculateViewMatrix();
	}

	void Camera::SetPosition(vec3 position)
	{
		Actor::SetPosition(position);
        CalculateViewMatrix();
	}

	void Camera::SetRotation(vec3 rotation)
	{
		Actor::SetRotation(rotation);
        CalculateViewMatrix();
	}

    void Camera::SetForward(vec3 forward)
    {
		Actor::SetForward(forward);
        CalculateViewMatrix();
    }

	void Camera::CalculateViewMatrix()
	{
		m_ViewMatrix = glm::lookAt(GetPosition(), GetPosition() + GetForward(), GetUp());
		m_CameraMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void Camera::CalculateProjectionMatrix()
	{
		m_ProjectionMatrix = glm::perspective(glm::radians(m_FOV), (float)m_Width / (float)m_Height, m_NearPlane, m_FarPlane);
		m_CameraMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void Camera::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowResizeEvent>(BIND_FN(Camera::OnWindowResized));
		dispatcher.Dispatch<KeyPressedEvent>(BIND_FN(Camera::OnKeyPressed));
		dispatcher.Dispatch<KeyReleasedEvent>(BIND_FN(Camera::OnKeyReleased));
	}

    bool Camera::OnWindowResized(WindowResizeEvent& event)
    {
        m_Width = Application::GetInstanceWindow().GetWidth();
        m_Height = Application::GetInstanceWindow().GetHeight();
        CalculateProjectionMatrix();
        return false;
    }

    bool Camera::OnKeyPressed(KeyPressedEvent& event)
    {
        int keyCode = event.GetKeyCode();
		if (keyCode == GLFW_KEY_LEFT_SHIFT)
			m_Speed = 10.0f;

        return false;
    }

    bool Camera::OnKeyReleased(KeyReleasedEvent& event)
    {
        int keyCode = event.GetKeyCode();
        if (keyCode == GLFW_KEY_ESCAPE)
        {
            m_Moving = !m_Moving;
            if (m_Moving)
                glfwSetInputMode(Application::GetInstanceNativeWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            else
                glfwSetInputMode(Application::GetInstanceNativeWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }

        if (keyCode == GLFW_KEY_LEFT_SHIFT)
            m_Speed = 5.0f;

        return false;
    }

	void Camera::OnUpdate(float deltaTime)
	{
		if (!m_Moving)
			return;

		if (Input::IsKeyPressed(GLFW_KEY_W))
			SetPosition(GetPosition() + m_Speed * GetForward() * deltaTime);
		if (Input::IsKeyPressed(GLFW_KEY_A))
			SetPosition(GetPosition() + m_Speed * -glm::normalize(glm::cross(GetForward(), GetUp())) * deltaTime);
		if (Input::IsKeyPressed(GLFW_KEY_S))
			SetPosition(GetPosition() + m_Speed * -GetForward() * deltaTime);
		if (Input::IsKeyPressed(GLFW_KEY_D))
			SetPosition(GetPosition() + m_Speed * glm::normalize(glm::cross(GetForward(), GetUp())) * deltaTime);
		if (Input::IsKeyPressed(GLFW_KEY_SPACE))
			SetPosition(GetPosition() + m_Speed * GetUp() * deltaTime);
		if (Input::IsKeyPressed(GLFW_KEY_LEFT_CONTROL))
			SetPosition(GetPosition() + m_Speed * -GetUp() * deltaTime);


        glm::vec2 mousePosition = Input::GetMousePosition();
		float rotX = m_Sensitivity * (float)(mousePosition.y - (m_Height / 2.0f)) / m_Height * deltaTime;
		float rotY = m_Sensitivity * (float)(mousePosition.x - (m_Width / 2.0f)) / m_Width * deltaTime;
		glm::vec3 newForward = glm::rotate(GetForward(), glm::radians(-rotX), glm::normalize(glm::cross(GetForward(), GetUp())));
		if (std::abs(glm::angle(newForward, GetUp()) - glm::radians(90.0f)) <= glm::radians(85.0f))
			SetForward(newForward);

		SetForward(glm::rotate(GetForward(), glm::radians(-rotY), GetUp()));
		glfwSetCursorPos(Application::GetInstanceNativeWindow(), (m_Width / 2.0f), (m_Height / 2.0f));
	}
}
