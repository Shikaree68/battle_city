#pragma once

#include <glad/glad.h>
#include <glm/mat4x4.hpp>
#include <string>

namespace RenderEngine {
	class ShaderProgram 
	{
	public:
		ShaderProgram (const std::string& vertex_shader, const std::string& fragment_shader);
		ShaderProgram() = delete;
		ShaderProgram(ShaderProgram&) = delete;
		ShaderProgram operator=(const ShaderProgram&) = delete;
		ShaderProgram& operator=(ShaderProgram&& shader_program) noexcept;
		ShaderProgram(ShaderProgram&& shader_program) noexcept;
		~ShaderProgram ();

		bool IsCompiled() const { return is_compiled_; }
		void Use() const;
		void SetInt(const std::string& name, const GLint value);
		void SetMatrix4(const std::string& name, const glm::mat4& matrix);

	private:
		bool CreateShader(const std::string& source, const GLenum shader_type, GLuint& ID);
		bool is_compiled_{ false };
		GLuint id_{ 0 };
	};

}