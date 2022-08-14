#ifndef INPUT_CLASS_H
#define INPUT_CLASS_H

#include "glm/glm.hpp"

namespace OpenGLRenderer
{
	class Input
	{
	public:
		Input() {};
		~Input() {};

		static bool IsKeyPressed(int keycode);
		static bool IsMouseButtonPressed(int button);
		static glm::vec2 GetMousePosition();
		static Input& GetInstance() { return *s_Instance; };

	private:
		static Input* s_Instance;
	};
}

#endif
