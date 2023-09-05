#include "resource_manager.h"

#include <fstream>
#include <iostream>
#include <sstream>

#include "../Renderer/shader_program.h"
#include "../Renderer/sprite.h"
#include "../Renderer/texture_2D.h"
#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#include "stb_image.h"
ResourceManager::ResourceManager(const std::string& executable_path) {
  size_t found{executable_path.find_last_of("/\\")};
  path_ = executable_path.substr(0, found);
}

std::shared_ptr<Renderer::ShaderProgram> ResourceManager::LoadShaders(
    const std::string& shader_name, const std::string& vertex_path,
    const std::string& fragment_path) {
  std::string vertex_string{GetFileString(vertex_path)};
  if (vertex_string.empty()) {
    std::cerr << "No vertex shader!" << std::endl;
    return nullptr;
  }

  std::string fragment_string{GetFileString(fragment_path)};
  if (fragment_string.empty()) {
    std::cerr << "No fragment shader!" << std::endl;
    return nullptr;
  }

  std::shared_ptr<Renderer::ShaderProgram>& new_shader{
      shader_programs_
          .emplace(shader_name, std::make_shared<Renderer::ShaderProgram>(
                                    vertex_string, fragment_string))
          .first->second};
  if (new_shader->IsCompiled()) {
    return new_shader;
  }
  std::cerr << "Can't load shader program:"
            << "\nVertex: " << vertex_path << "\nFragment: " << fragment_path
            << std::endl;
  return nullptr;
}

std::shared_ptr<Renderer::ShaderProgram> ResourceManager::GetShaderProgram(
    const std::string& shader_name) {
  ShaderProgramsMap::const_iterator it{shader_programs_.find(shader_name)};
  if (it != shader_programs_.end()) {
    return it->second;
  }
  std::cerr << "Can't find the shader program: " << shader_name << std::endl;
  return nullptr;
}

std::shared_ptr<Renderer::Texture2D> ResourceManager::LoadTexture(
    const std::string& texture_name, const std::string& texture_path) {
  int channels{};
  int width{};
  int height{};

  stbi_set_flip_vertically_on_load(true);
  unsigned char* pixels{
      stbi_load(std::string(path_ + '/' + texture_path).c_str(), &width,
                &height, &channels, 0)};

  if (!pixels) {
    std::cerr << "Can't load image: " << texture_path << std::endl;
    return nullptr;
  }

  std::shared_ptr<Renderer::Texture2D> new_texture{
      textures_
          .emplace(texture_name, std::make_shared<Renderer::Texture2D>(
                                     width, height, pixels, channels,
                                     GL_NEAREST, GL_CLAMP_TO_EDGE))
          .first->second};

  stbi_image_free(pixels);
  return new_texture;
}

std::shared_ptr<Renderer::Texture2D> ResourceManager::GetTexture(
    const std::string& texture_name) {
  TexturesMap::const_iterator it{textures_.find(texture_name)};
  if (it != textures_.end()) {
    return it->second;
  }
  std::cerr << "Can't find the texture: " << texture_name << std::endl;
  return nullptr;
}

std::shared_ptr<Renderer::Sprite> ResourceManager::LoadSprite(
    const std::string& sprite_name, const std::string& texture_name,
    const std::string& shader_name, const uint32_t sprite_width,
    const uint32_t sprite_height) {
  auto texture{GetTexture(texture_name)};
  if (!texture) {
    std::cerr << "Can't find texture: " << texture_name
              << " for the sprite: " << sprite_name << std::endl;
  }

  auto shader{GetShaderProgram(shader_name)};
  if (!shader) {
    std::cerr << "Can't find shader: " << shader_name
              << " for the sprite: " << sprite_name << std::endl;
  }
  std::shared_ptr<Renderer::Sprite> new_sprite{
      sprites_
          .emplace(sprite_name, std::make_shared<Renderer::Sprite>(
                                     texture, shader, glm::vec2(0.f, 0.f),
                                     glm::vec2(sprite_width, sprite_height)))
          .first->second};

  return new_sprite;
}

std::shared_ptr<Renderer::Sprite> ResourceManager::GetSprite(
    const std::string& sprite_name) {
  SpriteMap::const_iterator it{sprites_.find(sprite_name)};
  if (it != sprites_.end()) {
    return it->second;
  }
  std::cerr << "Can't find the sprite: " << sprite_name << std::endl;
  return nullptr;
}

std::string ResourceManager::GetFileString(
    const std::string& relative_path) const {
  std::ifstream ifs;
  ifs.open(path_ + '/' + relative_path.c_str(),
           std::ios::in | std::ios::binary);
  if (!ifs.is_open()) {
    std::cerr << "Failed to open file: " << relative_path << std::endl;
    return std::string{};
  }

  std::stringstream buffer;
  buffer << ifs.rdbuf();
  return buffer.str();
}
