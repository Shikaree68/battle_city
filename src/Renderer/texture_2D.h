#pragma once

#include <glad/glad.h>
#include <string>

namespace Renderer {
	class Texture2D 
	{
	public:
		Texture2D(const GLuint width, GLuint height, const unsigned char* data,
				const unsigned channels = 4, const GLenum filter = GL_LINEAR,
				const GLenum wrap_mode = GL_CLAMP_TO_EDGE);

		Texture2D& operator=(Texture2D&& texture_2d) noexcept;
		Texture2D(Texture2D&& texture_2d) noexcept;

		Texture2D() = delete;
		Texture2D(const Texture2D&) = delete;
		Texture2D& operator=(const Texture2D&) = delete;

		~Texture2D();

		void Bind() const;
	private:
		GLuint id_{ 0 };
		GLenum mode_;
		uint32_t width_;
		uint32_t height_;
	};
}