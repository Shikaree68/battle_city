#include "sprite.h"

#include "shader_program.h"
#include "texture_2D.h"
#include "renderer.h"

#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace RenderEngine{
Sprite::Sprite(std::shared_ptr<Texture2D> texture,
			   const std::string& initial_sub_texture,
			   std::shared_ptr<ShaderProgram> shader_program)
	: texture_(std::move(texture))
	, shader_program_(std::move(shader_program)){

	const GLfloat vertex_coords[]{
		//1--2
		//| /|
		//0--3

		//X  Y

		0.f, 0.f,
		0.f, 1.f,
		1.f, 1.f,
		1.f, 0.f,
	};

	auto& sub_texture{texture_->GetSubTexture(initial_sub_texture)};

	const GLfloat texture_coords[]{
		// U  V
		sub_texture.left_bottom_UV.x, sub_texture.left_bottom_UV.y,
		sub_texture.left_bottom_UV.x, sub_texture.right_top_UV.y,
		sub_texture.right_top_UV.x, sub_texture.right_top_UV.y,
		sub_texture.right_top_UV.x, sub_texture.left_bottom_UV.y,
	};

	const GLuint indices[]{
		// U  V
		0, 1, 2,
		2, 3, 0,
	};

	vertex_coords_buffer_.Initialize(vertex_coords, 2 * 4 * sizeof(GLfloat));
	VertexBufferLayout vertex_coords_layout;
	vertex_coords_layout.AddElementLayoutFloat(2, false);
	vertex_array_.AddBuffer(vertex_coords_buffer_, vertex_coords_layout);

	texuter_coords_buffer_.Initialize(texture_coords, 2 * 4 * sizeof(GLfloat));
	VertexBufferLayout texture_coords_layout;
	texture_coords_layout.AddElementLayoutFloat(2, false);
	vertex_array_.AddBuffer(texuter_coords_buffer_, texture_coords_layout);

	index_buffer_.Initialize(indices, 6);
	vertex_array_.Unbind();
	index_buffer_.Unbind();
}
Sprite::~Sprite(){}

void Sprite::Render(const glm::vec2& position, const glm::vec2& size, const float rotation) const{
	shader_program_->Use();

	glm::mat4 model(1.f);

	model = glm::translate(model, glm::vec3(position, 0.f));
	model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.f));
	model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.f, 0.f, 1.f));
	model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.f));
	model = glm::scale(model, glm::vec3(size, 1.f));

	shader_program_->SetMatrix4("model_matrix", model);

	glActiveTexture(GL_TEXTURE0);
	texture_->Bind();


	Renderer::Draw(vertex_array_, index_buffer_, *shader_program_);
}
}
