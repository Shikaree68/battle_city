#pragma once

#include "vertex_array.h"
#include "index_buffer.h"
#include "shader_program.h"

#include <glad/glad.h>
#include <glm/vec2.hpp>
#include <memory>
#include <string>

namespace RenderEngine {
class Renderer{
public:
	static void Draw(const VertexArray& vertex_array, const IndexBuffer& index_buffer, const ShaderProgram& shader);
	static void SetClearColor(float red, float green, float blue, float alpha);
	static void SetDepthTest(const bool enable);
	static void Clear();
	static void SetViewport(uint32_t width, uint32_t height, uint32_t left_offset = 0, uint32_t bottom_offset = 0);

	static std::string GetRenderType();
	static std::string GetRenderVersion();
};
}