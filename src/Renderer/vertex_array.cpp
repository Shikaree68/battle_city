#include "vertex_array.h"


namespace RenderEngine{
VertexArray::VertexArray(){
	glGenVertexArrays(1, &index_);
}
VertexArray::~VertexArray(){
	glDeleteVertexArrays(1, &index_);
}
VertexArray& VertexArray::operator=(VertexArray&& vertex_array) noexcept{
	index_ = vertex_array.index_;
	vertex_array.index_ = 0;
	return *this;
}
VertexArray::VertexArray(VertexArray&& vertex_array) noexcept{
	index_ = vertex_array.index_;
	vertex_array.index_ = 0;
}

void VertexArray::AddBuffer(const VertexBuffer& vertex_buffer, const VertexBufferLayout& layout){
	Bind();
	vertex_buffer.Bind();
	const auto& layout_elements = layout.GetLayoutElements();
	GLbyte* offset = nullptr;
	for(size_t i = 0, size = layout_elements.size(); i < size; ++i){
		const auto& current_layout_element = layout_elements[i];
		GLuint current_attrib_index = static_cast<GLuint>(elements_count_ + i);
		glEnableVertexAttribArray(current_attrib_index);
		glVertexAttribPointer(current_attrib_index, 
							  current_layout_element.count, 
							  current_layout_element.type, 
							  current_layout_element.normalized, 
							  layout.GetStride(), 
							  offset);
		offset += current_layout_element.size;
	}
	elements_count_ += layout_elements.size();
}

void VertexArray::Bind() const{
	glBindVertexArray(index_);
}
void VertexArray::Unbind() const{
	glBindVertexArray(0);
}
}
