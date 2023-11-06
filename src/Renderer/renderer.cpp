#include "renderer.h"

namespace RenderEngine {
void RenderEngine::Renderer::Draw(const VertexArray& vertex_array, const IndexBuffer& index_buffer, const ShaderProgram& shader) {
	shader.Use();
	vertex_array.Bind();
	index_buffer.Bind();

	glDrawElements(GL_TRIANGLES, index_buffer.GetCount(), GL_UNSIGNED_INT, nullptr);
}
void Renderer::SetClearColor(float red, float green, float blue, float alpha) {
	glClearColor(red, green, blue, alpha);
}
void Renderer::SetDepthTest(const bool enable) {
	if(enable) {
		glEnable(GL_DEPTH_TEST);
	} else {
		glDisable(GL_DEPTH_TEST);
	}
}
void Renderer::Clear() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void Renderer::SetViewport(uint32_t width, uint32_t height, uint32_t left_offset, uint32_t bottom_offset) {
	glViewport(left_offset, bottom_offset, width, height);
}
std::string Renderer::GetRenderType() {
	return (char*)glGetString(GL_RENDERER);
}
std::string Renderer::GetRenderVersion() {
	return (char*)glGetString(GL_VERSION);
}
}
