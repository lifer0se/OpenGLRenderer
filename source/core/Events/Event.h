#ifndef EVENT_CLASS_H
#define EVENT_CLASS_H

#define BIT(x) (1 << x)

enum class EventType
{
	None,
	WindowCloseEvent,
	WindowResizeEvent,
	WindowFocusEvent,
	WindowUnfocusEvent,
	UpdateEvent,
	RenderEvent,
	KeyPressedEvent,
	KeyReleasedEvent,
	MouseButtonPressedEvent,
	MouseButtonReleasedEvent,
	MouseScrolledEvent,
	MouseMovedEvent
};

enum EventCategory
{
	None = 0,
	EventCategoryApplication  = BIT(0),
	EventCategoryInput        = BIT(1),
	EventCategoryKeyboard     = BIT(2),
	EventCategoryMouse        = BIT(3),
	EventCategoryMouseButton  = BIT(4)
};

class Event
{
	friend class EventDispatcher;

 public:
	virtual ~Event() = default;

	bool Handled = false;

	virtual EventType GetEventType() const = 0;
	virtual const char* GetName() const = 0;
	virtual int GetCategoryFlags() const = 0;
	virtual std::string ToString() const { return GetName(); };

	bool IsInCategory(EventCategory category) { return GetCategoryFlags() & category; };
};

class EventDispatcher
{
 public:
    EventDispatcher(Event& event) : m_Event(event) {};

	template<typename T, typename F>
	bool Dispatch(const F& func)
	{
		if (m_Event.GetEventType() != T::GetStaticType())
			return false;

		m_Event.Handled |= func(static_cast<T&>(m_Event));
		return true;
	}

 private:
	Event& m_Event;
};

inline std::ostream &operator<<(std::ostream &os, const Event &e)
{
	return os << e.ToString();
}

#endif
