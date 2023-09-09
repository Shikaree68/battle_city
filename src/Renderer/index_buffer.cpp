#include "index_buffer.h"

namespace RenderEngine{
IndexBuffer::~IndexBuffer(){
	glDeleteBuffers(1, &index_);
}
IndexBuffer& IndexBuffer::operator=(IndexBuffer&& index_buffer) noexcept{
	index_ = index_buffer.index_;
	index_buffer.index_ = 0;
	count_ = index_buffer.count_;
	index_buffer.count_ = 0;
	return *this;
}
IndexBuffer::IndexBuffer(IndexBuffer&& index_buffer) noexcept{
	index_ = index_buffer.index_;
	index_buffer.index_ = 0;
	count_ = index_buffer.count_;
	index_buffer.count_ = 0;
}
void IndexBuffer::Initialize(const void* data, const uint32_t count){
	count_ = count;
	glGenBuffers(1, &index_);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_STATIC_DRAW);
}
void IndexBuffer::Bind() const{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_);
}
void IndexBuffer::Unbind() const{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
}
