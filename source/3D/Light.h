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
		~Light() {};
        void AddShader(std::shared_ptr<Shader> shader);
		void Translate(vec3 offset);
		void SetPosition(vec3 position);

		inline vec3 GetDiffuseColor() { return m_DiffuseColor; }
		inline vec3 GetSpecularColor() { return m_DiffuseColor; }
		inline vec3 GetAmbientColor() { return m_DiffuseColor; }

		void SetDiffuseColor(vec3 color);
		void SetSpecularColor(vec3 color);
		void SetAmbientColor(vec3 color);

	protected:
		vector<std::shared_ptr<Shader>> m_Shaders;
		vec3 m_DiffuseColor { 1.0f, 1.0f, 1.0f };
		vec3 m_SpecularColor { 1.0f, 1.0f, 1.0f };
		vec3 m_AmbientColor { 1.0f, 1.0f, 1.0f };

        void UpdateShaderLightPosition();
        void UpdateShaderLightColor(vec3& color);
	};

    class Directional : public Light
    {
    public:
        Directional() {};
        ~Directional() {};
    };

    class Point : public Light
    {
    public:
        Point() {};
        ~Point() {};

        float Constant;
        float Linear;
        float Quadratic;
    };

    class Spot : public Light
    {
    public:
        Spot() {};
        ~Spot() {};

        float CutOff;
        float OuterCutOff;

        float Constant;
        float Linear;
        float Quadratic;
    };
}

#endif
