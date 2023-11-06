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

	struct FrameDescription{
		FrameDescription(const glm::vec2 left_bottom_UV_, glm::vec2 right_top_UV_, uint64_t duration_)
			:left_bottom_UV(left_bottom_UV_)
			, right_top_UV(right_top_UV_)
			, duration(duration_){}
		glm::vec2 left_bottom_UV;
		glm::vec2 right_top_UV;
		uint64_t duration;
	};
	Sprite(std::shared_ptr<Texture2D> texture,
		   const std::string& initial_sub_texture,
		   std::shared_ptr<ShaderProgram> shader_program);
	~Sprite();

	Sprite(const Sprite&) = delete;
	Sprite& operator=(const Sprite&) = delete;

	void Render(const glm::vec2& position,
				const glm::vec2& size,
				const float rotation,
				const float layer = 0.f,
				const size_t frame_id = 0) const;

	void InsertFrames(std::vector<FrameDescription> frames_descriptions);
	uint64_t GetFrameDuration(const size_t frame_id) const;
	size_t GetFramesCount() const;

private:
	std::shared_ptr<Texture2D> texture_;
	std::shared_ptr<ShaderProgram> shader_program_;
	//GLuint vao_;

	VertexArray vertex_array_;
	VertexBuffer vertex_coords_buffer_;
	VertexBuffer texuter_coords_buffer_;
	IndexBuffer index_buffer_;

	std::vector<FrameDescription> frames_decriptions_;
	mutable size_t last_frame_id_;

};
}  // namespace Renderer