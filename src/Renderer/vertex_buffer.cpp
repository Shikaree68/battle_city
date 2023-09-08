#include "vertex_buffer.h"

namespace Renderer{
VertexBuffer::VertexBuffer(): index_(0){}
VertexBuffer::~VertexBuffer(){
	glDeleteBuffers(1, &index_);
}
VertexBuffer& VertexBuffer::operator=(VertexBuffer&& vertex_buffer){
	index_ = vertex_buffer.index_;
	vertex_buffer.index_ = 0;
	return *this;
}
VertexBuffer::VertexBuffer(VertexBuffer&& vertex_buffer){
	index_ = vertex_buffer.index_;
	vertex_buffer.index_ = 0;
}
void VertexBuffer::Initialize(const void* data, const uint32_t size){
	glGenBuffers(1, &index_);
	glBindBuffer(GL_ARRAY_BUFFER, index_);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}
void VertexBuffer::Update(const void* data, const uint32_t size) const{
	glBindBuffer(GL_ARRAY_BUFFER, index_);
	glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}
void VertexBuffer::Bind() const{
	glBindBuffer(GL_ARRAY_BUFFER, index_);
}
void VertexBuffer::Unbind() const{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
}
