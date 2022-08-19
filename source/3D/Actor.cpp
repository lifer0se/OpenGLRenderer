#include "Actor.h"
#include "Application.h"

namespace OpenGLRenderer
{
	vec3 Actor::GetPosition() {	return m_Position; }
	vec3 Actor::GetForward() { return m_Forward; }
	vec3 Actor::GetRight() { return m_Right; }
	vec3 Actor::GetUp() { return m_Up; }
	vec3 Actor::GetRotation() { return m_Rotation; }
	vec3 Actor::GetScale() { return m_Scale; }

	void Actor::Translate(vec3 offset) { m_Position += offset; }
	void Actor::SetPosition(vec3 position) { m_Position = position; }
	void Actor::SetForward(vec3 forward) { m_Forward = forward; }
	void Actor::SetRight(vec3 right) { m_Right = right; }
	void Actor::SetUp(vec3 up) { m_Up = up; }
	void Actor::SetRotation(vec3 rotation) { m_Rotation = rotation; }
	void Actor::SetScale(vec3 scale) { m_Scale = scale; }

    void Actor::OnUpdate(float deltaTime) {}

    void Actor::AddChild(std::shared_ptr<Actor> child)
    {
        m_Children[child->GetName()] = child;
        Application::GetInstance().GetScene().AddActor(child);
    }
}
