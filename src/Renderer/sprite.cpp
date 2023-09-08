#include "sprite.h"

#include "shader_program.h"
#include "texture_2D.h"

#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace Renderer{
Sprite::Sprite(std::shared_ptr<Texture2D> texture,
			   const std::string& initial_sub_texture,
			   std::shared_ptr<ShaderProgram> shader_program,
			   const glm::vec2& position,
			   const glm::vec2& size,
			   const float rotation)
	: texture_(std::move(texture))
	, shader_program_(std::move(shader_program))
	, position_(position)
	, size_(size)
	, rotation_(rotation){

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

	glGenVertexArrays(1, &vao_);
	glBindVertexArray(vao_);

	vertex_coords_buffer_.Initialize(vertex_coords, 2 * 4 * sizeof(GLfloat));

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

	texuter_coords_buffer_.Initialize(texture_coords, 2 * 4 * sizeof(GLfloat));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

	index_buffer_.Initialize(indices, 6 * sizeof(GLuint));


	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
Sprite::~Sprite(){
	glDeleteVertexArrays(1, &vao_);
}
void Sprite::Render() const{
	shader_program_->Use();

	glm::mat4 model(1.f);

	model = glm::translate(model, glm::vec3(position_, 0.f));
	model = glm::translate(model, glm::vec3(0.5f * size_.x, 0.5f * size_.y, 0.f));
	model = glm::rotate(model, glm::radians(rotation_), glm::vec3(0.f, 0.f, 1.f));
	model = glm::translate(model, glm::vec3(-0.5f * size_.x, -0.5f * size_.y, 0.f));
	model = glm::scale(model, glm::vec3(size_, 1.f));

	glBindVertexArray(vao_);
	shader_program_->SetMatrix4("model_matrix", model);

	glActiveTexture(GL_TEXTURE0);
	texture_->Bind();

	//glDrawArrays(GL_TRIANGLES, 0, 6);
	glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT, nullptr);
	glBindVertexArray(0);

}
void Sprite::SetPosition(const glm::vec2& position){
	position_ = position;
}
void Sprite::SetSize(const glm::vec2& size){
	size_ = size;
}
void Sprite::SetRotation(const float rotation){
	rotation_ = rotation;
}
}
