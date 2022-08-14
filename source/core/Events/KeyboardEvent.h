#ifndef KEYBOARD_EVENT_CLASS_H
#define KEYBOARD_EVENT_CLASS_H

#include "Event.h"

class KeyEvent : public Event
{
 public:
	inline int GetKeyCode() const { return m_KeyCode; };

 protected:
	KeyEvent(int keycode) : m_KeyCode(keycode) {};
	virtual int GetCategoryFlags() const override { return EventCategoryKeyboard | EventCategoryInput; };

	int m_KeyCode;
};

class KeyPressedEvent : public KeyEvent
{
 public:
    KeyPressedEvent(int keyCode, bool repeated) : KeyEvent(keyCode), m_Repeated(repeated) {};

	static EventType GetStaticType() { return EventType::KeyPressedEvent; };
	virtual EventType GetEventType() const override { return GetStaticType(); };
	virtual const char* GetName() const override { return "KeyPressed"; };

	bool Repeated() const { return m_Repeated; };
	std::string ToString() const override
	{
		std::string s = "KeyPressedEvent: " + std::to_string(m_KeyCode) + (m_Repeated ? " (repeated)" : "" );
		return s;
	}

 private:
	bool m_Repeated;
};

class KeyReleasedEvent : public KeyEvent
{
 public:
    KeyReleasedEvent(int keyCode) : KeyEvent(keyCode) {};

	static EventType GetStaticType() { return EventType::KeyReleasedEvent; };
	virtual EventType GetEventType() const override { return GetStaticType(); };
	virtual const char* GetName() const override { return "KeyReleased"; };

	std::string ToString() const override
	{
		std::string s = "KeyReleasedEvent: " + std::to_string(m_KeyCode);
		return s;
	}
};

#endif
