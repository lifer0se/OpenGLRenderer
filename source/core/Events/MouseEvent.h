#ifndef MOUSE_EVENT_CLASS_H
#define MOUSE_EVENT_CLASS_H

#include "Event.h"

class MouseMovedEvent : public Event
{
 public:
	MouseMovedEvent(const float x, const float y) : m_MouseX(x), m_MouseY(y) {}

	float GetX() const { return m_MouseX; }
	float GetY() const { return m_MouseY; }
	std::string ToString() const override
	{
		std::string s = "MouseMovedEvent: " + std::to_string(m_MouseX) + ", " + std::to_string(m_MouseY);
		return s;
	}

	static EventType GetStaticType() { return EventType::MouseMovedEvent; };
	virtual EventType GetEventType() const override { return GetStaticType(); };
	virtual const char* GetName() const override { return "MouseMoved"; };
	virtual int GetCategoryFlags() const override { return EventCategoryMouse | EventCategoryInput; };

	private:
		float m_MouseX, m_MouseY;
};
class MouseScrolledEvent : public Event
{
 public:
 MouseScrolledEvent(float xOffset, float yOffset)
	 : m_XOffset(xOffset), m_YOffset(yOffset) {}

	inline float GetXOffset() const { return m_XOffset; }
	inline float GetYOffset() const { return m_YOffset; }

	std::string ToString() const override
	{
		std::string s = "MouseScrolledEvent: " + std::to_string(GetXOffset()) + ", " + std::to_string(GetYOffset());
		return s;
	}

	static EventType GetStaticType() { return EventType::MouseScrolledEvent; };
	virtual EventType GetEventType() const override { return GetStaticType(); };
	virtual const char* GetName() const override { return "MouseScrolled"; };
	virtual int GetCategoryFlags() const override { return EventCategoryMouse | EventCategoryInput; };

 private:
	float m_XOffset, m_YOffset;
};

class MouseButtonEvent : public Event
{
 public:
	int GetMouseButton() const { return m_Button; }
	virtual int GetCategoryFlags() const override { return EventCategoryMouse | EventCategoryInput; };

 protected:
    MouseButtonEvent(const int button) : m_Button(button) {}

	int m_Button;
};

class MouseButtonPressedEvent : public MouseButtonEvent
{
 public:
    MouseButtonPressedEvent(const int button) : MouseButtonEvent(button) {}
	std::string ToString() const override
	{
		std::string s = "MouseButtonPressedEvent: " + std::to_string(m_Button);
		return s;
	}

	static EventType GetStaticType() { return EventType::MouseButtonPressedEvent; };
	virtual EventType GetEventType() const override { return GetStaticType(); };
	virtual const char* GetName() const override { return "MouseButtonPressed"; };
};

class MouseButtonReleasedEvent : public MouseButtonEvent
{
 public:
    MouseButtonReleasedEvent(const int button) : MouseButtonEvent(button) {}
	std::string ToString() const override
	{
		std::string s = "MouseButtonReleasedEvent: " + std::to_string(m_Button);
		return s;
	}

	static EventType GetStaticType() { return EventType::MouseButtonReleasedEvent; };
	virtual EventType GetEventType() const override { return GetStaticType(); };
	virtual const char* GetName() const override { return "MouseButtonReleased"; };

};

#endif
