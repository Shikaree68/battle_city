#pragma once

#include <glad/glad.h>
#include <stdint.h>

namespace RenderEngine{

class VertexBuffer{
public:
	VertexBuffer();
	~VertexBuffer();

	VertexBuffer(const VertexBuffer&) = delete;
	VertexBuffer& operator=(const VertexBuffer&) = delete;
	VertexBuffer& operator=(VertexBuffer&& vertex_buffer) noexcept;
	VertexBuffer(VertexBuffer&& vertex_buffer) noexcept;

	void Initialize(const void* data, const uint32_t size);
	void Update(const void* data, const uint32_t size) const;
	void Bind() const;
	void Unbind() const;

private:
	GLuint index_;
};
}  // namespace Renderer