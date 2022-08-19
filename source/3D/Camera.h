#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include "Events/ApplicationEvent.h"
#include "Events/KeyboardEvent.h"
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "Actor.h"
#include "Shader.h"

namespace OpenGLRenderer
{
	class Camera : public Actor
	{
	public:
		Camera() {};
		Camera(float FOVdeg, float nearPlane, float farPlane);

        void Translate(vec3 offset);
        void SetPosition(vec3 position);
        void SetRotation(vec3 rotation);
        void SetForward(vec3 forward);

        void SetWidth(int width) { m_Width = width; };
        void SetHeight(int height) { m_Height = height; };

        const mat4& GetCameraMatrix() const { return m_CameraMatrix; };
        const mat4& GetViewMatrix() const { return m_ViewMatrix; };
        const mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; };
		void UpdateMatrix(float FOVdeg, int width, int height, float nearPlane, float farPlane);

        void CalculateViewMatrix();
        void CalculateProjectionMatrix();

        void OnEvent(Event& event);
        virtual void OnUpdate(float deltaTime) override;

	private:
        bool OnWindowResized(WindowResizeEvent& event);
        bool OnKeyPressed(KeyPressedEvent& event);
        bool OnKeyReleased(KeyReleasedEvent& event);

		glm::mat4 m_CameraMatrix = glm::mat4(1.0f);
		glm::mat4 m_ViewMatrix = glm::mat4(1.0f);
		glm::mat4 m_ProjectionMatrix = glm::mat4(1.0f);

		bool m_EscapePressed = false;
		bool m_Moving = false;

		int m_Width;
		int m_Height;
        float m_FOV;
        float m_NearPlane;
        float m_FarPlane;
		float m_Speed = 5.0f;
		float m_Sensitivity = 1500.0f;
	};
}

#endif
