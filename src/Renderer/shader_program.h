#pragma once

#include <glad/glad.h>
#include <string>

namespace Renderer {
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

		//ShaderProgram() = default;
	private:
		bool CreateShader(const std::string& source, const GLenum shader_type, GLuint& ID);
		bool is_compiled_{ false };
		GLuint id_{ 0 };
	};

}