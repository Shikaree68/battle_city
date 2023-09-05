#include "sprite.h"

#include "shader_program.h"
#include "texture_2D.h"

#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace Renderer {
    Sprite::Sprite(std::shared_ptr<Texture2D> texture, 
        std::shared_ptr<ShaderProgram> shader_program, 
        const glm::vec2& position, 
        const glm::vec2& size, 
        const float rotation)
        : texture_(std::move(texture))
        , shader_program_(std::move(shader_program))
        , position_(position)
        , size_(size)
        , rotation_(rotation)
    {

        const GLfloat vertex_coords[]
        {
            //2--3....1
            //|./.../.|
            //1....3--2

            //X  Y

            0.f, 0.f,
            0.f, 1.f,
            1.f, 1.f,

            1.f, 1.f,
            1.f, 0.f,
            0.f, 0.f,
        };

        const GLfloat texture_coords[]
        {
            // U  V

            0.f, 0.f,
            0.f, 1.f,
            1.f, 1.f,

            1.f, 1.f,
            1.f, 0.f,
            0.f, 0.f,
        };

        glGenVertexArrays(1, &vao_);
        glBindVertexArray(vao_);

        glGenBuffers(1, &vertex_coords_vbo_);
        glBindBuffer(GL_ARRAY_BUFFER, vertex_coords_vbo_);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_coords), &vertex_coords, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

        glGenBuffers(1, &texture_coords_vbo_);
        glBindBuffer(GL_ARRAY_BUFFER, texture_coords_vbo_);
        glBufferData(GL_ARRAY_BUFFER, sizeof(texture_coords), &texture_coords, GL_STATIC_DRAW);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
    Sprite::~Sprite()
    {
        glDeleteBuffers(1, &vertex_coords_vbo_);
        glDeleteBuffers(1, &texture_coords_vbo_);
        glDeleteVertexArrays(1, &vao_);
    }
    void Sprite::Render() const
    {
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

        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);

    }
    void Sprite::SetPosition(const glm::vec2& position)
    {
        position_ = position;
    }
    void Sprite::SetSize(const glm::vec2& size)
    {
        size_ = size;
    }
    void Sprite::SetRotation(const float rotation)
    {
        rotation_ = rotation;
    }
}
