#ifndef OBJECT_CLASS_H
#define OBJECT_CLASS_H

namespace OpenGLRenderer
{
	class Object
	{
	public:
		Object(){};
		Object(const char* name) { m_Name = name; };
		void SetName(const char* name) { m_Name = name; };
		virtual const char* GetName() { return m_Name; };
		bool operator==(Object other) { return m_Name == other.GetName(); };

	protected:
		const char* m_Name;
	};
}

#endif
