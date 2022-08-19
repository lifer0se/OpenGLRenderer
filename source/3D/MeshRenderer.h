#ifndef MESHRENDERER_CLASS_H
#define MESHRENDERER_CLASS_H

#include "Actor.h"
#include "Mesh.h"
#include "Shader.h"
#include "VertexArrayBuffer.h"
#include "IndicesBuffer.h"
#include "Camera.h"
#include "Texture.h"
#include <memory>

using namespace std;

namespace OpenGLRenderer
{
	class MeshRenderer : public Actor
	{
	public:
		MeshRenderer() {};
		~MeshRenderer() { LOG_TRACE("Deconstructed::MeshRenderer::{0}", m_Name); };
		MeshRenderer(std::shared_ptr<Shader> shader, Mesh mesh, const char* name);

		void Draw(Camera& camera);
		Mesh* GetMesh() { return &m_Mesh; };
		std::shared_ptr<Shader> GetShader() { return m_Shader; };
		void SetMesh(Mesh mesh) { m_Mesh = mesh; };
		void Translate(vec3 offset);
		void SetPosition(vec3 position);
		void SetRotation(vec3 rotation);
		void SetScale(vec3 scale);

        inline void SetTransparent(bool status) { m_Transparent = status; };

        void Rotate(vec3 axis, float angle);

	private:
		VertexArrayBuffer m_VertexArrayBuffer;
		Mesh m_Mesh;
        std::shared_ptr<Shader> m_Shader;
		mat4 m_TranslationMatrix { 1.0f };
		mat4 m_RotationMatrix { 1.0f };
		mat4 m_ScaleMatrix { 1.0f };
        bool m_Transparent { false };

		void InitializeMesh();
        void SetModelMatrix();
	};
}

#endif
