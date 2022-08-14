#ifndef INDICESBUFFER_CLASS_H
#define INDICESBUFFER_CLASS_H

#include "glad/glad.h"

using namespace std;

namespace OpenGLRenderer
{
	class IndicesBuffer
	{
	public:
		GLuint ID;
		IndicesBuffer(vector<GLuint>& indices);

		void Bind();
		void Unbind();
		void Delete();
	};
}

#endif
