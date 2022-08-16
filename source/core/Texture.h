#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include "Shader.h"

namespace OpenGLRenderer
{
	class Texture
	{
	public:
		const char* type;
		Texture(const char* image, const char* texType, GLuint slot);
        static unsigned int LoadTexture(char const * path);

        inline GLuint GetID() { return m_ID; };

		void Bind();
		void Unbind();
		void Delete();

    private:
        GLuint m_ID;
	};
}

#endif
