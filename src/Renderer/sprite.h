#pragma once

#include "vertex_buffer.h"
#include "index_buffer.h"
#include "vertex_array.h"

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
         const std::string& initial_sub_texture,
         std::shared_ptr<ShaderProgram> shader_program,
         const glm::vec2& position = glm::vec2(0.f),
         const glm::vec2& size = glm::vec2(1.f), const float rotation = 0.f);
  virtual ~Sprite();

  Sprite(const Sprite&) = delete;
  Sprite& operator=(const Sprite&) = delete;

  virtual void Render() const ;
  void SetPosition(const glm::vec2& position);
  void SetSize(const glm::vec2& size);
  void SetRotation(const float rotation);

 protected:
  std::shared_ptr<Texture2D> texture_;
  std::shared_ptr<ShaderProgram> shader_program_;
  glm::vec2 position_;
  glm::vec2 size_;
  float rotation_;
  GLuint vao_;

  VertexArray vertex_array_;
  VertexBuffer vertex_coords_buffer_;
  VertexBuffer texuter_coords_buffer_;
  IndexBuffer index_buffer_;

};
}  // namespace Renderer