#include "kmpch.h"

#include "Shader.h"
#include "filesystem"
#include <Glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace fs = std::filesystem;

namespace Komet {

	Shader::Shader(const char* vertexSrc, const char* fragmentSrc)
	{
		std::string vertexShaderSource = readFile(vertexSrc);
		std::string fragmentShaderSource = readFile(fragmentSrc);

		const char* vertexSourceCStr = vertexShaderSource.c_str();	
		const char* fragmentSourceCStr = fragmentShaderSource.c_str();

		unsigned int vertex, fragment;

		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vertexSourceCStr, nullptr);
		glCompileShader(vertex);

		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fragmentSourceCStr, nullptr);
		glCompileShader(fragment);


		m_RendererID = glCreateProgram();
		glAttachShader(m_RendererID, vertex);
		glAttachShader(m_RendererID, fragment);
		glLinkProgram(m_RendererID);

		glDeleteShader(vertex);
		glDeleteShader(fragment);

	}

	void Shader::Bind() const
	{
		glUseProgram(m_RendererID);
	}

	void Shader::Unbind() const
	{
		glUseProgram(0);
	}
	void Shader::SetInt(const std::string& name, int value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		if (location != -1)
			glUniform1i(location, value);
		else
			KM_CORE_WARN("Uniform '{0}' not found!", name);
	}

	void Shader::SetFloat3(const std::string& name, const glm::vec3& value) {
		glUniform3f(glGetUniformLocation(m_RendererID, name.c_str()), value.x, value.y, value.z);
	}

	void Shader::SetFloat(const std::string& name, float value) {
		glUniform1f(glGetUniformLocation(m_RendererID, name.c_str()), value);
	}

	void Shader::SetMat4(const std::string& name, const glm::mat4& value) {
		glUniformMatrix4fv(glGetUniformLocation(m_RendererID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
	}

	std::string Shader::readFile(const char* filepath)
	{
		std::ifstream file;
		std::stringstream buffer;
		file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try {
			file.open(filepath);
			buffer << file.rdbuf();
			file.close();
		}
		catch (std::ifstream::failure& e)
		{
			std::cout << "Failure: " << e.what() << std::endl;
			KM_CORE_ERROR("Failed to read shader file: {0}", filepath);
		}
		return buffer.str();
	}
}