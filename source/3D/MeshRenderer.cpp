#include "MeshRenderer.h"
#include "Logger.h"
#include "Mesh.h"

namespace OpenGLRenderer
{
	MeshRenderer::MeshRenderer(std::shared_ptr<Shader> shader, Mesh mesh, const char* name)
	{
		m_Shader = shader;
		m_Mesh = mesh;
        SetName(name);
		InitializeMesh();
        LOG_TRACE("Constructed::MeshRenderer::{0}", m_Name);
	}

	void MeshRenderer::Translate(vec3 offset)
	{
		Actor::Translate(offset);
		m_TranslationMatrix = translate(mat4 { 1.0f }, GetPosition());
	}

	void MeshRenderer::SetPosition(vec3 position)
	{
		Actor::SetPosition(position);
		m_TranslationMatrix = translate(mat4 { 1.0f }, position);
	}

	void MeshRenderer::SetRotation(vec3 rotation)
	{
		Actor::SetRotation(rotation);
		quat q { rotation };
		m_RotationMatrix = mat4_cast(q);
	}

	void MeshRenderer::SetScale(vec3 scale)
	{
		Actor::SetScale(scale);
		m_ScaleMatrix = glm::scale(mat4 { 1.0f }, scale);
	}

	void MeshRenderer::InitializeMesh()
	{
		m_VertexArrayBuffer.Bind();

		VerticesBuffer verticesBuffer(m_Mesh.Vertices);
		IndicesBuffer indicesBuffer(m_Mesh.Indices);

		m_VertexArrayBuffer.LinkAttributes(verticesBuffer, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
		m_VertexArrayBuffer.LinkAttributes(verticesBuffer, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
		m_VertexArrayBuffer.LinkAttributes(verticesBuffer, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));
		m_VertexArrayBuffer.LinkAttributes(verticesBuffer, 3, 2, GL_FLOAT, sizeof(Vertex), (void*)(9 * sizeof(float)));

		m_VertexArrayBuffer.Unbind();
		verticesBuffer.Unbind();
		indicesBuffer.Unbind();

        m_Shader->Activate();
        m_Shader->SetMat4("translation", m_TranslationMatrix);

		unsigned int numDiffuse = 0;
		unsigned int numSpecular = 0;
		for (unsigned int i = 0; i < m_Mesh.Textures.size(); i++)
		{
			std::string num;
			std::string type = m_Mesh.Textures[i].type;
			if (type == "diffuse")
				num = std::to_string(numDiffuse++);
			else if (type == "specular")
				num = std::to_string(numSpecular++);

            m_Shader->SetInt(type + num, i);
			m_Mesh.Textures[i].Bind();
		}
	}

	void MeshRenderer::Draw(Camera* camera)
	{
		m_Shader->Activate();
		m_VertexArrayBuffer.Bind();

        m_Shader->SetVec3("camPos", camera->GetPosition());
        m_Shader->SetMat4("camMatrix", camera->GetCameraMatrix());

        m_Shader->SetMat4("translation", m_TranslationMatrix);
        m_Shader->SetMat4("rotation", m_RotationMatrix);
        m_Shader->SetMat4("scale", m_ScaleMatrix);

		glDrawElements(GL_TRIANGLES, m_Mesh.Indices.size(), GL_UNSIGNED_INT, nullptr);
	}
}
