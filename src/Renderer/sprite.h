#pragma once


#include <glad/glad.h>
#include <glm/vec2.hpp>
#include <memory>
#include <string>

namespace Renderer {

class Texture2D;
class ShaderProgram;

class Sprite {
 public:
  Sprite(std::shared_ptr<Texture2D> texture,
         std::shared_ptr<ShaderProgram> shader_program,
         const glm::vec2& position = glm::vec2(0.f),
         const glm::vec2& size = glm::vec2(1.f), const float rotation = 1.f);
  ~Sprite();

  Sprite(const Sprite&) = delete;
  Sprite& operator=(const Sprite&) = delete;

  void Render() const;
  void SetPosition(const glm::vec2& position);
  void SetSize(const glm::vec2& size);
  void SetRotation(const float rotation);

 private:
  std::shared_ptr<Texture2D> texture_;
  std::shared_ptr<ShaderProgram> shader_program_;
  glm::vec2 position_;
  glm::vec2 size_;
  float rotation_;
  GLuint vao_;
  // объединить в один
  GLuint vertex_coords_vbo_;
  GLuint texture_coords_vbo_;
};
}  // namespace Renderer