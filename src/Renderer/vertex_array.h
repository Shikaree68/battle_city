#pragma once

#include "vertex_buffer.h"
#include "vertex_buffer_layout.h"

#include <glad/glad.h>
#include <stdint.h>

namespace RenderEngine {

class VertexArray{
public:
	VertexArray();
	~VertexArray();

	VertexArray(const VertexArray&) = delete;
	VertexArray& operator=(const VertexArray&) = delete;
	VertexArray& operator=(VertexArray&& vertex_array) noexcept;
	VertexArray(VertexArray&& vertex_array) noexcept;

	void AddBuffer(const VertexBuffer& vertex_buffer, const VertexBufferLayout& layout);
	void Bind() const;
	void Unbind() const;

private:
	GLuint index_ = 0;
	uint32_t elements_count_ = 0;
};
}  // namespace Renderer