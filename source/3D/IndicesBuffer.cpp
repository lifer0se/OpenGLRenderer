#include "IndicesBuffer.h"

namespace OpenGLRenderer
{
	IndicesBuffer::IndicesBuffer(vector<GLuint>& indices)
	{
		glGenBuffers(1, &ID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
	}

	void IndicesBuffer::Bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	}

	void IndicesBuffer::Unbind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void IndicesBuffer::Delete()
	{
		glDeleteBuffers(1, &ID);
	}
}
