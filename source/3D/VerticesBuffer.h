#ifndef VERTICESBUFFER_CLASS_H
#define VERTICESBUFFER_CLASS_H

#include "glad/glad.h"
#include "Mesh.h"

namespace OpenGLRenderer
{
	class VerticesBuffer
	{
	public:
		GLuint ID;
		VerticesBuffer(vector<Vertex> vertices);

		void Bind();
		void Unbind();
		void Delete();
	};
}

#endif
