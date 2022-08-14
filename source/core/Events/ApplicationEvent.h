#include "Event.h"

class WindowResizeEvent : public Event
{
 public:
    WindowResizeEvent(unsigned int width, unsigned int height)
		: m_Width(width), m_Height(height) {}

	unsigned int GetWidth() const { return m_Width; }
	unsigned int GetHeight() const { return m_Height; }
	std::string ToString() const override
	{
		std::string s = "WindowResizeEvent: " + std::to_string(m_Width) + ", " + std::to_string(m_Height);
		return s;
	}

	static EventType GetStaticType() { return EventType::WindowResizeEvent; };
	virtual EventType GetEventType() const override { return GetStaticType(); };
	virtual const char* GetName() const override { return "WindowResize"; };
	virtual int GetCategoryFlags() const override { return EventCategoryApplication; };

 private:
	unsigned int m_Width, m_Height;
};

class WindowCloseEvent : public Event
{
 public:
	WindowCloseEvent() = default;

	static EventType GetStaticType() { return EventType::WindowCloseEvent; };
	virtual EventType GetEventType() const override { return GetStaticType(); };
	virtual const char* GetName() const override { return "WindowClose"; };
	virtual int GetCategoryFlags() const override { return EventCategoryApplication; };
};

class UpdateEvent : public Event
{
 public:
	UpdateEvent() = default;

	static EventType GetStaticType() { return EventType::UpdateEvent; };
	virtual EventType GetEventType() const override { return GetStaticType(); };
	virtual const char* GetName() const override { return "Update"; };
	virtual int GetCategoryFlags() const override { return EventCategoryApplication; };
};
