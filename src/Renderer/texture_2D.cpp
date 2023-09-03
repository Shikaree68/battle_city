
#include "texture_2D.h"

namespace Renderer {
	Texture2D::Texture2D(const GLuint width, GLuint height,
		const unsigned char* data, const unsigned channels,
		const GLenum filter, const GLenum wrap_mode)
		: width_(width), height_(height)
	{
		switch (channels)
		{
		case 4: 
			mode_ = GL_RGBA;
			break;
		case 3: 
			mode_ = GL_RGB;
			break;
		default:
			mode_ = GL_RGBA;
			break;
		}

		glGenTextures(1, &id_);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, id_);
		glTexImage2D(GL_TEXTURE_2D, 0, mode_, width_, height_, 0, mode_, GL_UNSIGNED_BYTE, data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_mode);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_mode);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);
	}
	Texture2D& Texture2D::operator=(Texture2D&& texture_2d) noexcept
	{
		glDeleteTextures(1, &id_);
		id_		= texture_2d.id_;
		texture_2d.id_ = 0;
		mode_	= texture_2d.mode_;
		width_	= texture_2d.width_;
		height_ = texture_2d.height_;
		return *this;
	}
	Texture2D::Texture2D(Texture2D&& texture_2d) noexcept
	{
		id_		= texture_2d.id_;
		texture_2d.id_ = 0;
		mode_	= texture_2d.mode_;
		width_	= texture_2d.width_;
		height_ = texture_2d.height_;
	}
	Texture2D::~Texture2D()
	{
		glDeleteTextures(1, &id_);
	}
	void Texture2D::Bind() const
	{
		glBindTexture(GL_TEXTURE_2D, id_);
	}
}
