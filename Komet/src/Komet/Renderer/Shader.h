#pragma once

#include <string>
#include <glm/glm.hpp>

namespace Komet {
	class Shader
	{
	public:

		Shader(const char* vertexSrc, const char* fragmentSrc);

		void Bind() const;
		void Unbind() const;

		void SetInt(const std::string& name, int value);
		void SetFloat(const std::string& name, float value);
		void SetFloat3(const std::string& name, const glm::vec3& value);

		void SetMat4(const std::string& name, const glm::mat4& value);

		uint32_t m_RendererID;
	private:
		static std::string readFile(const char* filepath);
	};
}