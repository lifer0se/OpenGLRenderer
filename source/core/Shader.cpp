#include "Shader.h"

namespace OpenGLRenderer
{
    std::string read_get_file(const char *path)
	{
		std::ifstream in(path, std::ios::binary);
		if (in)
		{
			std::string contents;
			in.seekg(0, std::ios::end);
			contents.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&contents[0], contents.size());
			in.close();
			return(contents);
		}
		throw (errno);
	}

	Shader::Shader(const char *vertFile, const char *fragFile)
	{
        std::string vert = read_get_file(vertFile);
        std::string frag = read_get_file(fragFile);
		const char* vertSource = vert.c_str();
		const char* fragSource = frag.c_str();

		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertSource, NULL);
		glCompileShader(vertexShader);
		compileErrors(vertexShader, "VERTEX");

		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragSource, NULL);
		glCompileShader(fragmentShader);
		compileErrors(fragmentShader, "FRAGMENT");

		m_ID = glCreateProgram();
		glAttachShader(m_ID, vertexShader);
		glAttachShader(m_ID, fragmentShader);
		glLinkProgram(m_ID);
		compileErrors(m_ID, "PROGRAM");

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
        LOG_TRACE("Constructed::Shader::{0}", m_ID);
	}

	void Shader::Activate()
	{
		glUseProgram(m_ID);
	}

	void Shader::Delete()
	{
		glDeleteProgram(m_ID);
	}

    void Shader::SetBool(const std::string &name, bool value) const
    {
        glUniform1i(glGetUniformLocation(m_ID, name.c_str()), (int)value);
    }

    void Shader::SetInt(const std::string &name, int value) const
    {
        glUniform1i(glGetUniformLocation(m_ID, name.c_str()), value);
    }

    void Shader::SetFloat(const std::string &name, float value) const
    {
        glUniform1f(glGetUniformLocation(m_ID, name.c_str()), value);
    }

    void Shader::SetVec2(const std::string &name, const glm::vec2 &value) const
    {
        glUniform2fv(glGetUniformLocation(m_ID, name.c_str()), 1, &value[0]);
    }

    void Shader::SetVec2(const std::string &name, float x, float y) const
    {
        glUniform2f(glGetUniformLocation(m_ID, name.c_str()), x, y);
    }

    void Shader::SetVec3(const std::string &name, const glm::vec3 &value) const
    {
        glUniform3fv(glGetUniformLocation(m_ID, name.c_str()), 1, &value[0]);
    }

    void Shader::SetVec3(const std::string &name, float x, float y, float z) const
    {
        glUniform3f(glGetUniformLocation(m_ID, name.c_str()), x, y, z);
    }

    void Shader::SetVec4(const std::string &name, const glm::vec4 &value) const
    {
        glUniform4fv(glGetUniformLocation(m_ID, name.c_str()), 1, &value[0]);
    }

    void Shader::SetVec4(const std::string &name, float x, float y, float z, float w) const
    {
        glUniform4f(glGetUniformLocation(m_ID, name.c_str()), x, y, z, w);
    }

    void Shader::SetMat2(const std::string &name, const glm::mat2 &mat) const
    {
        glUniformMatrix2fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    void Shader::SetMat3(const std::string &name, const glm::mat3 &mat) const
    {
        glUniformMatrix3fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    void Shader::SetMat4(const std::string &name, const glm::mat4 &mat) const
    {
        glUniformMatrix4fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

	// Checks if the different Shaders have compiled properly
	void Shader::compileErrors(unsigned int shader, const char* type)
	{
		// Stores status of compilation
		GLint hasCompiled;
		// Character array to store error message in
		char infoLog[1024];
		if (type != "PROGRAM")
		{
			glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
			if (hasCompiled == GL_FALSE)
			{
				glGetShaderInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "SHADER_COMPILATION_ERROR for:" << type << "\n" << infoLog << std::endl;
			}
		}
		else
		{
			glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled);
			if (hasCompiled == GL_FALSE)
			{
				glGetProgramInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "SHADER_LINKING_ERROR for:" << type << "\n" << infoLog << std::endl;
			}
		}
	}
}
