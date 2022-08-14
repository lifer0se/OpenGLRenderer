#ifndef LIGHT_CLASS_H
#define LIGHT_CLASS_H

#include "Actor.h"
#include "Shader.h"

using namespace std;

namespace OpenGLRenderer
{
	class Light : public Actor
	{
	public:
		Light() {};
        void AddShader(std::shared_ptr<Shader> shader);
		void Translate(vec3 offset);
		void SetPosition(vec3 position);
		void SetColor(vec4 color);

	private:
		vector<std::shared_ptr<Shader>> m_Shaders;
		vec4 m_Color { 1.0f, 1.0f, 1.0f, 1.0f };

        void UpdateShaderLightPosition();
        void UpdateShaderLightColor();
	};
}

#endif
