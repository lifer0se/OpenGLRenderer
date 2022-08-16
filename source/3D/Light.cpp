#include "Light.h"

namespace OpenGLRenderer
{
	void Light::AddShader(std::shared_ptr<Shader> shader)
	{
		m_Shaders.push_back(shader);
		shader->Activate();
        shader->SetVec3("lightPos", GetPosition());

        vec3 d = m_DiffuseColor;
        shader->SetVec4("lightColor", { d.r, d.g, d.b, 1.0f });
        LOG_TRACE("Light::AddShader::{0}", shader->GetID());
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

    void Light::SetDiffuseColor(vec3 color)
    {
		m_DiffuseColor = color;
        UpdateShaderLightColor(color);
    }

    void Light::SetSpecularColor(vec3 color)
    {
		m_SpecularColor = color;
        UpdateShaderLightColor(color);
    }

    void Light::SetAmbientColor(vec3 color)
    {
		m_AmbientColor = color;
        UpdateShaderLightColor(color);
    }

    void Light::UpdateShaderLightPosition()
    {
        for (std::shared_ptr<Shader> shader : m_Shaders)
        {
            shader->Activate();
            shader->SetVec3("lightPos", GetPosition());
        }
    }

    void Light::UpdateShaderLightColor(vec3& color)
    {
        for (std::shared_ptr<Shader> shader : m_Shaders)
        {
            shader->Activate();

            vec3 d = m_DiffuseColor;
            shader->SetVec4("lightColor", { d.r, d.g, d.b, 1.0f });
        }
    }
}
