#include "VertexArrayBuffer.h"

namespace OpenGLRenderer
{
	VertexArrayBuffer::VertexArrayBuffer()
	{
		glGenVertexArrays(1, &ID);
	}

	void VertexArrayBuffer::LinkAttributes(VerticesBuffer& VerticesBuffer, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset)
	{
		VerticesBuffer.Bind();
		glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
		glEnableVertexAttribArray(layout);
		VerticesBuffer.Unbind();
	}

	void VertexArrayBuffer::Bind()
	{
		glBindVertexArray(ID);
	}

	void VertexArrayBuffer::Unbind()
	{
		glBindVertexArray(0);
	}

	void VertexArrayBuffer::Delete()
	{
		glDeleteVertexArrays(1, &ID);
	}
}
