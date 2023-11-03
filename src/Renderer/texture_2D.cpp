
#include "texture_2D.h"

namespace RenderEngine {
Texture2D::Texture2D(GLuint width, GLuint height,
                     const unsigned char* data, const unsigned channels,
                     const GLenum filter, const GLenum wrap_mode)
    : size_(width, height) {
  switch (channels) {
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
  glTexImage2D(GL_TEXTURE_2D, 0, mode_, size_.width, size_.height, 0, mode_,
               GL_UNSIGNED_BYTE, data);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_mode);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_mode);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
  glGenerateMipmap(GL_TEXTURE_2D);

  glBindTexture(GL_TEXTURE_2D, 0);
}
Texture2D& Texture2D::operator=(Texture2D&& texture_2d) noexcept {
  glDeleteTextures(1, &id_);
  id_ = texture_2d.id_;
  texture_2d.id_ = 0;
  mode_ = texture_2d.mode_;
  size_ = texture_2d.size_;

  return *this;
}
Texture2D::Texture2D(Texture2D&& texture_2d) noexcept {
  id_ = texture_2d.id_;
  texture_2d.id_ = 0;
  mode_ = texture_2d.mode_;
  size_ = texture_2d.size_;
}
Texture2D::~Texture2D() { glDeleteTextures(1, &id_); }
void Texture2D::Addsubtexture(std::string name, const glm::vec2& left_bottom_uv,
                              const glm::vec2& right_top_uv) {
  sub_textures_.emplace(std::move(name),
                        subtexture2d(left_bottom_uv, right_top_uv));
}
const Texture2D::subtexture2d& Texture2D::Getsubtexture(const std::string& name) const {
  auto it{sub_textures_.find(name)};
  if (it != sub_textures_.end()) {
    return it->second;
  }
  const static subtexture2d default_sub_texture;
  return default_sub_texture;
}
void Texture2D::Bind() const { glBindTexture(GL_TEXTURE_2D, id_); }
}  // namespace Renderer
