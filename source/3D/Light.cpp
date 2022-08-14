#include "Light.h"

namespace OpenGLRenderer
{
	void Light::AddShader(std::shared_ptr<Shader> shader)
	{
		m_Shaders.push_back(shader);
		shader->Activate();
        shader->SetVec3("lightPos", GetPosition());
        shader->SetVec4("lightColor", m_Color);
	}

	void Light::Translate(vec3 offset)
	{
		Actor::Translate(offset);
        UpdateShaderLightPosition();
	}

	void Light::SetPosition(vec3 position)
	{
		Actor::SetPosition(position);
        UpdateShaderLightPosition();
	}

	void Light::SetColor(vec4 color)
	{
		m_Color = color;
        UpdateShaderLightColor();
	}

    void Light::UpdateShaderLightPosition()
    {
        for (std::shared_ptr<Shader> shader : m_Shaders)
        {
            shader->Activate();
            shader->SetVec3("lightPos", GetPosition());
        }
    }

    void Light::UpdateShaderLightColor()
    {
        for (std::shared_ptr<Shader> shader : m_Shaders)
        {
            shader->Activate();
            shader->SetVec4("lightColor", m_Color);
        }
    }
}
