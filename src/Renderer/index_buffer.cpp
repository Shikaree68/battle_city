#include "index_buffer.h"

namespace Renderer{
IndexBuffer::IndexBuffer(): index_(0){}
IndexBuffer::~IndexBuffer(){
	glDeleteBuffers(1, &index_);
}
IndexBuffer& IndexBuffer::operator=(IndexBuffer&& index_buffer){
	index_ = index_buffer.index_;
	index_buffer.index_ = 0;
	return *this;
}
IndexBuffer::IndexBuffer(IndexBuffer&& index_buffer){
	index_ = index_buffer.index_;
	index_buffer.index_ = 0;
}
void IndexBuffer::Initialize(const void* data, const uint32_t size){
	glGenBuffers(1, &index_);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}
void IndexBuffer::Bind() const{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_);
}
void IndexBuffer::Unbind() const{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
}
