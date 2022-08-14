#ifndef VERTEXARRAYBUFFER_CLASS_H
#define VERTEXARRAYBUFFER_CLASS_H

#include "glad/glad.h"
#include "VerticesBuffer.h"

namespace OpenGLRenderer
{
	class VertexArrayBuffer
	{
	public:
		GLuint ID;
        VertexArrayBuffer();
		~VertexArrayBuffer() {};

		void LinkAttributes(VerticesBuffer& VerticesBuffer, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
		void Bind();
		void Unbind();
		void Delete();
	};
}

#endif
