#pragma once


#include <glad/glad.h>
#include <stdint.h>

namespace RenderEngine {

class IndexBuffer{
public:
	IndexBuffer(){};
	~IndexBuffer();

	IndexBuffer(const IndexBuffer&) = delete;
	IndexBuffer& operator=(const IndexBuffer&) = delete;
	IndexBuffer& operator=(IndexBuffer&& index_buffer) noexcept;
	IndexBuffer(IndexBuffer&& index_buffer) noexcept;

	void Initialize(const void* data, const uint32_t count);
	void Bind() const;
	void Unbind() const;
	uint32_t GetCount() const{
		return count_;
	};

private:
	GLuint index_ = 0;
	uint32_t count_ = 0;
};
}  // namespace Renderer