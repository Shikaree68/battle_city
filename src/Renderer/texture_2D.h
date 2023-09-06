#pragma once

#include <glad/glad.h>
#include <glm/vec2.hpp>

#include <string>
#include <map>

namespace Renderer {
class Texture2D {
 public:
  struct SubTexture2d {
    glm::vec2 left_bottom_UV;
    glm::vec2 right_top_UV;
    SubTexture2d(const glm::vec2& _left_bottom_UV,
                 const glm::vec2& _right_top_UV)
        : left_bottom_UV(_left_bottom_UV), right_top_UV(_right_top_UV) {}
    SubTexture2d() : left_bottom_UV(0.f), right_top_UV(1.f) {}
  };

  struct Size {
    uint32_t width{};
    uint32_t height{};
    Size(){};
    Size(GLuint w, GLint h) : width(w), height(h){};
  };

  Texture2D(GLuint width, GLuint height, const unsigned char* data,
            const unsigned channels = 4, const GLenum filter = GL_LINEAR,
            const GLenum wrap_mode = GL_CLAMP_TO_EDGE);

  Texture2D& operator=(Texture2D&& texture_2d) noexcept;
  Texture2D(Texture2D&& texture_2d) noexcept;
  ~Texture2D();

  Texture2D() = delete;
  Texture2D(const Texture2D&) = delete;
  Texture2D& operator=(const Texture2D&) = delete;

  void AddSubTexture(std::string name, const glm::vec2& left_bottom_uv,
                     const glm::vec2& right_top_uv);
  const SubTexture2d& GetSubTexture(const std::string& name) const;
  Size GetSize() const { return size_; };

  void Bind() const;

 private:
  GLuint id_{0};
  GLenum mode_;
  Size size_;
  std::map<std::string, SubTexture2d> sub_textures_;
};
}  // namespace Renderer