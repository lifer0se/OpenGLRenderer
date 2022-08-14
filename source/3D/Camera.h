#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include "Application.h"
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
		void UpdateMatrix(float FOVdeg, int width, int height, float nearPlane, float farPlane);

        void CalculateViewMatrix();
        void CalculateProjectionMatrix();

        void OnEvent(Event& event);
        void OnUpdate();

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
		float m_Speed = 0.05f;
		float m_Sensitivity = 50.0f;
	};
} // namespace OpenGLRenderer

#endif
