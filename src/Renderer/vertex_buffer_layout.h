#pragma once


#include <glad/glad.h>
#include <stdint.h>
#include <vector>

namespace RenderEngine {
struct VertexBufferLayoutElement{
	GLint count;
	GLenum type;
	GLboolean normalized;
	size_t size;
};

class VertexBufferLayout{
public:
	VertexBufferLayout();

	void ReserveElements(const size_t count);
	uint32_t GetStride() const{
		return stride_;
	}
	void AddElementLayoutFloat(const int32_t count, const bool normilozed);
	const std::vector<VertexBufferLayoutElement>& GetLayoutElements() const{
		return layout_elements_;
	}
private:
	std::vector<VertexBufferLayoutElement> layout_elements_;
	uint32_t stride_;
};
}  // namespace Renderer