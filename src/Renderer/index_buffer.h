#pragma once


#include <glad/glad.h>
#include <stdint.h>

namespace Renderer {

class IndexBuffer{
public:
	IndexBuffer();
	~IndexBuffer();

	IndexBuffer(const IndexBuffer&) = delete;
	IndexBuffer& operator=(const IndexBuffer&) = delete;
	IndexBuffer& operator=(IndexBuffer&& index_buffer);
	IndexBuffer(IndexBuffer&& index_buffer);

	void Initialize(const void* data, const uint32_t size);
	void Bind() const;
	void Unbind() const;

private:
	GLuint index_;
};
}  // namespace Renderer