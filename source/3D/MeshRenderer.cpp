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
        offset = { offset.x, -offset.y, offset.z };
		m_TranslationMatrix = translate(mat4 { 1.0f }, GetPosition());
        SetModelMatrix();
	}

	void MeshRenderer::SetPosition(vec3 position)
	{
		Actor::SetPosition(position);
        position = { position.x, -position.y, position.z };
		m_TranslationMatrix = translate(mat4 { 1.0f }, position);

        m_Shader->Activate();
        m_Shader->SetMat4("translation", m_TranslationMatrix);
	}

	void MeshRenderer::SetRotation(vec3 rotation)
	{
		Actor::SetRotation(rotation);
		quat q { rotation };

		m_RotationMatrix = toMat4(q);
        SetModelMatrix();
	}

    void MeshRenderer::Rotate(vec3 axis, float angle)
    {
        m_RotationMatrix = rotate(angle, axis);
        SetModelMatrix();
    }

	void MeshRenderer::SetScale(vec3 scale)
	{
		Actor::SetScale(scale);
		m_ScaleMatrix = glm::scale(mat4 { 1.0f }, scale);
        SetModelMatrix();
	}

    void MeshRenderer::SetModelMatrix()
    {
        m_Shader->Activate();
        m_Shader->SetMat4("model", m_TranslationMatrix * m_RotationMatrix * m_ScaleMatrix);
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
        m_Shader->SetMat4("model", m_TranslationMatrix * m_RotationMatrix * m_ScaleMatrix);
	}

	void MeshRenderer::Draw(Camera& camera)
	{
        if (m_Transparent)
            glEnable(GL_BLEND);

		m_VertexArrayBuffer.Bind();

        m_Shader->Activate();
        m_Shader->SetMat4("view", camera.GetViewMatrix());
        m_Shader->SetMat4("projection", camera.GetProjectionMatrix());

		glDrawElements(GL_TRIANGLES, m_Mesh.Indices.size(), GL_UNSIGNED_INT, nullptr);
		m_VertexArrayBuffer.Unbind();

        if (m_Transparent)
            glDisable(GL_BLEND);
	}
}
