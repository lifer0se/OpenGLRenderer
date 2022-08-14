#include "VerticesBuffer.h"

namespace OpenGLRenderer
{
	VerticesBuffer::VerticesBuffer(vector<Vertex> vertices)
	{
		glGenBuffers(1, &ID);
		glBindBuffer(GL_ARRAY_BUFFER, ID);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
	}

	void VerticesBuffer::Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, ID);
	}

	void VerticesBuffer::Unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	void VerticesBuffer::Delete()
	{
		glDeleteBuffers(1, &ID);
	}
}
