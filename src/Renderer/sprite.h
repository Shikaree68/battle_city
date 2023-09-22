#pragma once

#include "vertex_buffer.h"
#include "index_buffer.h"
#include "vertex_array.h"

#include <glad/glad.h>
#include <glm/vec2.hpp>
#include <memory>
#include <string>

namespace RenderEngine{

class Texture2D;
class ShaderProgram;

class Sprite{
public:
	Sprite(std::shared_ptr<Texture2D> texture,
		   const std::string& initial_sub_texture,
		   std::shared_ptr<ShaderProgram> shader_program);
	virtual ~Sprite();

	Sprite(const Sprite&) = delete;
	Sprite& operator=(const Sprite&) = delete;

	virtual void Render(const glm::vec2& position, const glm::vec2& size, const float rotation) const;

protected:
	std::shared_ptr<Texture2D> texture_;
	std::shared_ptr<ShaderProgram> shader_program_;
	//GLuint vao_;

	VertexArray vertex_array_;
	VertexBuffer vertex_coords_buffer_;
	VertexBuffer texuter_coords_buffer_;
	IndexBuffer index_buffer_;

};
}  // namespace Renderer