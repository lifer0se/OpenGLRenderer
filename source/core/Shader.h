#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"


namespace OpenGLRenderer
{
	std::string read_get_file(const char *path0);

	class Shader
	{
	public:
		GLuint ID;
		Shader() {};
		~Shader() { LOG_TRACE("Deconstructed::Shader::{0}", ID); };
		Shader(const char* vertFile, const char* fragFile);

		void Activate();
		void Delete();

    void SetBool(const std::string &name, bool value) const;
    void SetInt(const std::string &name, int value) const;
    void SetFloat(const std::string &name, float value) const;
    void SetVec2(const std::string &name, const glm::vec2 &value) const;
    void SetVec2(const std::string &name, float x, float y) const;
    void SetVec3(const std::string &name, const glm::vec3 &value) const;
    void SetVec3(const std::string &name, float x, float y, float z) const;
    void SetVec4(const std::string &name, const glm::vec4 &value) const;
    void SetVec4(const std::string &name, float x, float y, float z, float w) const;
    void SetMat2(const std::string &name, const glm::mat2 &mat) const;
    void SetMat3(const std::string &name, const glm::mat3 &mat) const;
    void SetMat4(const std::string &name, const glm::mat4 &mat) const;

	private:
		void compileErrors(unsigned int shader, const char* type);
	};
}

#endif
