#include "resource_manager.h"

#include <fstream>
#include <iostream>
#include <sstream>

#include "../Renderer/shader_program.h"
#include "../Renderer/texture_2D.h"
#include "../Renderer/sprite.h"
#include "../Renderer/animated_sprite.h"


#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#include "stb_image.h"

ResourceManager::ShaderProgramsMap ResourceManager::shader_programs_;
ResourceManager::TexturesMap ResourceManager::textures_;
ResourceManager::SpritesMap ResourceManager::sprites_;
ResourceManager::AnimatedSpritesMap ResourceManager::animated_sprites_;
std::string ResourceManager::path_;

void ResourceManager::SetExecutablePath(const std::string& executable_path){
	size_t found = executable_path.find_last_of("/\\");
	path_ = executable_path.substr(0, found);
}

void ResourceManager::UnloadAllResources(){
	shader_programs_.clear();
	textures_.clear();
	sprites_.clear();
	animated_sprites_.clear();
}

std::shared_ptr<Renderer::ShaderProgram> ResourceManager::LoadShaders(const std::string& shader_name,
																	  const std::string& vertex_path,
																	  const std::string& fragment_path){
	std::string vertex_str = GetFileString(vertex_path);
	if(vertex_str.empty()){
		std::cerr << "No vertex shader!" << std::endl;
		return nullptr;
	}

	std::string fragment_str = GetFileString(fragment_path);
	if(fragment_str.empty()){
		std::cerr << "No fragment shader!" << std::endl;
		return nullptr;
	}

	std::shared_ptr<Renderer::ShaderProgram>& new_shader = shader_programs_.emplace(
		shader_name, std::make_shared<Renderer::ShaderProgram>(vertex_str, fragment_str)).first->second;
	if(new_shader->IsCompiled()){
		return new_shader;
	}
	std::cerr << "Can't load shader program:"
		<< "\nVertex: " << vertex_path << "\nFragment: " << fragment_path
		<< std::endl;
	return nullptr;
}

std::shared_ptr<Renderer::ShaderProgram> ResourceManager::GetShaderProgram(const std::string& shader_name){
	ShaderProgramsMap::const_iterator it = shader_programs_.find(shader_name);
	if(it != shader_programs_.end()){
		return it->second;
	}
	std::cerr << "Can't find the shader program: " << shader_name << std::endl;
	return nullptr;
}

std::shared_ptr<Renderer::Texture2D>
ResourceManager::LoadTexture(const std::string& texture_name, const std::string& texture_path){
	int channels = 0;
	int width = 0;
	int height = 0;

	stbi_set_flip_vertically_on_load(true);
	unsigned char* pixels = stbi_load(std::string(path_ + '/' + texture_path).c_str(), &width, &height, &channels, 0);

	if(!pixels){
		std::cerr << "Can't load image: " << texture_path << std::endl;
		return nullptr;
	}

	std::shared_ptr<Renderer::Texture2D> new_texture = textures_.emplace(texture_name, std::make_shared<Renderer::Texture2D>(
		width, height, pixels, channels, GL_NEAREST, GL_CLAMP_TO_EDGE)).first->second;
	stbi_image_free(pixels);

	return new_texture;
}

std::shared_ptr<Renderer::Texture2D>ResourceManager::GetTexture(const std::string& texture_name){
	TexturesMap::const_iterator it = textures_.find(texture_name);
	if(it != textures_.end()){
		return it->second;
	}
	std::cerr << "Can't find the texture: " << texture_name << std::endl;
	return nullptr;
}

std::shared_ptr<Renderer::Sprite> ResourceManager::LoadSprite(const std::string& sprite_name,
															  const std::string& texture_name,
															  const std::string& shader_name,
															  const uint32_t sprite_width,
															  const uint32_t sprite_height,
															  const std::string& sub_texture_name){
	auto texture{GetTexture(texture_name)};
	if(!texture){
		std::cerr << "Can't find texture: " << texture_name << " for the sprite: " << sprite_name << std::endl;
	}

	auto shader{GetShaderProgram(shader_name)};
	if(!shader){
		std::cerr << "Can't find shader: " << shader_name << " for the sprite: " << sprite_name << std::endl;
	}
	std::shared_ptr<Renderer::Sprite> new_sprite = sprites_.emplace(sprite_name, std::make_shared<Renderer::Sprite>(
		texture, sub_texture_name, shader, glm::vec2(0.f, 0.f), glm::vec2(sprite_width, sprite_height))).first->second;

	return new_sprite;
}

std::shared_ptr<Renderer::Sprite> ResourceManager::GetSprite(const std::string& sprite_name){
	SpritesMap::const_iterator sprite = sprites_.find(sprite_name);
	if(sprite != sprites_.end()){
		return sprite->second;
	}
	std::cerr << "Can't find the sprite: " << sprite_name << std::endl;
	return nullptr;
}

std::shared_ptr<Renderer::AnimatedSprite> ResourceManager::LoadAnimatedSprite(const std::string& sprite_name,
																			  const std::string& texture_name,
																			  const std::string& shader_name,
																			  const uint32_t sprite_width,
																			  const uint32_t sprite_height,
																			  const std::string& sub_texture_name){
	auto texture = GetTexture(texture_name);
	if(!texture){
		std::cerr << "Can't find texture: " << texture_name << " for the sprite: " << sprite_name << std::endl;
	}

	auto shader = GetShaderProgram(shader_name);
	if(!shader){
		std::cerr << "Can't find shader: " << shader_name << " for the sprite: " << sprite_name << std::endl;
	}
	std::shared_ptr<Renderer::AnimatedSprite> new_sprite = animated_sprites_.emplace(sprite_name, std::make_shared<Renderer::AnimatedSprite>(
		texture, sub_texture_name, shader, glm::vec2(0.f, 0.f), glm::vec2(sprite_width, sprite_height))).first->second;

	return new_sprite;
}

std::shared_ptr<Renderer::AnimatedSprite> ResourceManager::GetAnimatedSprite(const std::string& sprite_name){
	auto sprite = animated_sprites_.find(sprite_name);
	if(sprite != animated_sprites_.end()){
		return sprite->second;
	}
	std::cerr << "Can't find the animated sprite: " << sprite_name << std::endl;
	return nullptr;
}

std::shared_ptr<Renderer::Texture2D> ResourceManager::LoadTextureAtlas(const std::string& texture_name,
																	   const std::string& texture_path,
																	   const std::vector<std::string>& sub_textures_names,
																	   const uint32_t sub_texture_width,
																	   const uint32_t sub_texture_height){
	std::shared_ptr<Renderer::Texture2D> texture{LoadTexture(texture_name, texture_path)};
	if(texture){
		const uint32_t texture_width = texture->GetSize().width;
		const uint32_t texture_height = texture->GetSize().height;
		uint32_t current_texture_offset_x = 0;
		uint32_t current_texture_offset_y = texture_height;

		for(const auto& current_sub_texture_name : sub_textures_names){
			glm::vec2 left_bottom_UV{static_cast<float>(current_texture_offset_x) / texture_width,
				static_cast<float>(current_texture_offset_y - sub_texture_height) / texture_height};
			glm::vec2 right_top_UV{static_cast<float>(current_texture_offset_x + sub_texture_width) / texture_width,
				static_cast<float>(current_texture_offset_y) / texture_height};

			texture->AddSubTexture(current_sub_texture_name, left_bottom_UV, right_top_UV);

			current_texture_offset_x += sub_texture_width;

			if(current_texture_offset_x >= texture_width){
				current_texture_offset_x = 0;
				current_texture_offset_y -= sub_texture_height;
			}
		}
	}
	return texture;
}

std::string ResourceManager::GetFileString(const std::string& relative_path) {
	std::ifstream ifs;
	ifs.open(path_ + '/' + relative_path.c_str(), std::ios::in | std::ios::binary);
	if(!ifs.is_open()){
		std::cerr << "Failed to open file: " << relative_path << std::endl;
		return std::string{};
	}

	std::stringstream buffer;
	buffer << ifs.rdbuf();
	return buffer.str();
}
