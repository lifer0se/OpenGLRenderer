#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include "Shader.h"

namespace OpenGLRenderer
{
	class Texture
	{
	public:
		GLuint ID;
		const char* type;
		Texture(const char* image, const char* texType, GLuint slot);

		void Bind();
		void Unbind();
		void Delete();
	};
}

#endif
