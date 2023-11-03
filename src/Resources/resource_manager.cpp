#include "resource_manager.h"
#include "../Renderer/shader_program.h"
#include "../Renderer/texture_2D.h"
#include "../Renderer/sprite.h"

#include <fstream>
#include <iostream>
#include <sstream>

#include <rapidjson/document.h>
#include <rapidjson/error/en.h>

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#include "stb_image.h"

using namespace std::literals;

ResourceManager::ShaderProgramsMap ResourceManager::shader_programs_;
ResourceManager::TexturesMap ResourceManager::textures_;
ResourceManager::SpritesMap ResourceManager::sprites_;
std::string ResourceManager::path_;
std::vector<std::vector<std::string>> ResourceManager::levels_;

void ResourceManager::SetExecutablePath(const std::string& executable_path){
	size_t found = executable_path.find_last_of("/\\"sv);
	path_ = executable_path.substr(0, found);
}

void ResourceManager::UnloadAllResources(){
	shader_programs_.clear();
	textures_.clear();
	sprites_.clear();
}

std::shared_ptr<RenderEngine::ShaderProgram> ResourceManager::LoadShaders(const std::string& shader_name,
																		  const std::string& vertex_path,
																		  const std::string& fragment_path){
	std::string vertex_str = GetFileString(vertex_path);
	if(vertex_str.empty()){
		std::cerr << "No vertex shader!"sv << std::endl;
		return nullptr;
	}

	std::string fragment_str = GetFileString(fragment_path);
	if(fragment_str.empty()){
		std::cerr << "No fragment shader!"sv << std::endl;
		return nullptr;
	}

	std::shared_ptr<RenderEngine::ShaderProgram>& new_shader = shader_programs_.emplace(
		shader_name, std::make_shared<RenderEngine::ShaderProgram>(vertex_str, fragment_str)).first->second;
	if(new_shader->IsCompiled()){
		return new_shader;
	}
	std::cerr << "Can't load shader program:"sv
		<< "\nVertex: "sv << vertex_path << "\nFragment: "sv << fragment_path
		<< std::endl;
	return nullptr;
}

std::shared_ptr<RenderEngine::ShaderProgram> ResourceManager::GetShaderProgram(const std::string& shader_name){
	ShaderProgramsMap::const_iterator it = shader_programs_.find(shader_name);
	if(it != shader_programs_.end()){
		return it->second;
	}
	std::cerr << "Can't find the shader program: "sv << shader_name << std::endl;
	return nullptr;
}

std::shared_ptr<RenderEngine::Texture2D>
ResourceManager::LoadTexture(const std::string& texture_name, const std::string& texture_path){
	int channels = 0;
	int width = 0;
	int height = 0;

	stbi_set_flip_vertically_on_load(true);
	unsigned char* pixels = stbi_load(std::string(path_ + '/' + texture_path).c_str(), &width, &height, &channels, 0);

	if(!pixels){
		std::cerr << "Can't load image: "sv << texture_path << std::endl;
		return nullptr;
	}

	std::shared_ptr<RenderEngine::Texture2D> new_texture = textures_.emplace(texture_name, std::make_shared<RenderEngine::Texture2D>(
		width, height, pixels, channels, GL_NEAREST, GL_CLAMP_TO_EDGE)).first->second;
	stbi_image_free(pixels);

	return new_texture;
}

std::shared_ptr<RenderEngine::Texture2D>ResourceManager::GetTexture(const std::string& texture_name){
	TexturesMap::const_iterator it = textures_.find(texture_name);
	if(it != textures_.end()){
		return it->second;
	}
	std::cerr << "Can't find the texture: "sv << texture_name << std::endl;
	return nullptr;
}

std::shared_ptr<RenderEngine::Sprite> ResourceManager::LoadSprite(const std::string& sprite_name,
																  const std::string& texture_name,
																  const std::string& shader_name,
																  const std::string& sub_texture_name){
	auto texture{GetTexture(texture_name)};
	if(!texture){
		std::cerr << "Can't find texture: "sv << texture_name << " for the sprite: "sv << sprite_name << std::endl;
	}

	auto shader{GetShaderProgram(shader_name)};
	if(!shader){
		std::cerr << "Can't find shader: "sv << shader_name << " for the sprite: "sv << sprite_name << std::endl;
	}
	std::shared_ptr<RenderEngine::Sprite> new_sprite = sprites_.emplace(sprite_name, std::make_shared<RenderEngine::Sprite>(
		texture, sub_texture_name, shader)).first->second;

	return new_sprite;
}

std::shared_ptr<RenderEngine::Sprite> ResourceManager::GetSprite(const std::string& sprite_name){
	SpritesMap::const_iterator sprite = sprites_.find(sprite_name);
	if(sprite != sprites_.end()){
		return sprite->second;
	}
	std::cerr << "Can't find the sprite: "sv << sprite_name << std::endl;
	return nullptr;
}


bool ResourceManager::LoadJsonResources(const std::string& json_path){
	const std::string json_string = GetFileString(json_path);
	if(json_string.empty()){

		std::cerr << "No JSON resources file!"sv << std::endl;
		return false;
	}

	rapidjson::Document document;
	rapidjson::ParseResult parse_result = document.Parse(json_string.c_str());
	if(!parse_result){
		std::cerr << "JSON parse error: "sv << rapidjson::GetParseError_En(parse_result.Code())
			<< '(' << parse_result.Offset() << ')' << std::endl;
		std::cerr << "In JSON file: "sv << json_path << std::endl;
		return false;
	}

	auto shaders = document.FindMember("shaders");
	if(shaders != document.MemberEnd()){
		for(const auto& current_shader : shaders->value.GetArray()){
			const std::string name = current_shader["name"].GetString();
			const std::string filepath_v = current_shader["filepath_v"].GetString();
			const std::string filepath_f = current_shader["filepath_f"].GetString();
			LoadShaders(name, filepath_v, filepath_f);
		}
	}

	auto texture_atlases = document.FindMember("texture_atlases");
	if(texture_atlases != document.MemberEnd()){
		for(const auto& current_texture_atlas : texture_atlases->value.GetArray()){
			const std::string name = current_texture_atlas["name"].GetString();
			const std::string filepath = current_texture_atlas["filepath"].GetString();
			const uint32_t subtexture_width = current_texture_atlas["subtexture_width"].GetUint();
			const uint32_t subtexture_height = current_texture_atlas["subtexture_height"].GetUint();
			const auto subtextures_array = current_texture_atlas["subtextures"].GetArray();

			std::vector<std::string> subtextures;
			subtextures.reserve(subtextures_array.Size());
			for(const auto& current_subtexture : subtextures_array){
				subtextures.push_back(current_subtexture.GetString());
			}

			LoadTexture_atlas(name, filepath, subtextures, subtexture_width, subtexture_height);
		}
	}

	auto sprites = document.FindMember("sprites");
	if(sprites != document.MemberEnd()){
		for(const auto& current_sprite : sprites->value.GetArray()){
			const std::string name = current_sprite["name"].GetString();
			const std::string texture_atlas = current_sprite["texture_atlas"].GetString();
			const std::string shader = current_sprite["shader"].GetString();
			const std::string subtexture = current_sprite["initial_subtexture"].GetString();

			auto sprite = LoadSprite(name, texture_atlas, shader, subtexture);
			if(!sprite){
				continue;
			}
			auto frames = current_sprite.FindMember("frames");
			if(frames != current_sprite.MemberEnd()){
				const auto frames_array = frames->value.GetArray();
				std::vector<RenderEngine::Sprite::FrameDescription> frames_descriptions;
				frames_descriptions.reserve(frames_array.Size());

				for(const auto& current_frame : frames_array){
					const std::string subtexture = current_frame["subtexture"].GetString();
					const uint64_t duration = current_frame["duration"].GetUint64();
					const auto texture_atlas_ptr = GetTexture(texture_atlas);
					const auto subtexture_ptr = texture_atlas_ptr->Getsubtexture(subtexture);
					frames_descriptions.emplace_back(subtexture_ptr.left_bottom_UV, subtexture_ptr.right_top_UV, duration);
				}
				sprite->InsertFrames(std::move(frames_descriptions));
			}
		}
	}

	auto levels = document.FindMember("levels");
	if(levels != document.MemberEnd()){
		for(const auto& current_level : levels->value.GetArray()){
			const auto description = current_level["description"].GetArray();
			std::vector<std::string> level_rows;
			level_rows.reserve(description.Size());
			size_t max_length = 0;
			for(const auto& level_row : description){
				level_rows.emplace_back(level_row.GetString());
				if(max_length < level_rows.back().length()){
					max_length = level_rows.back().length();
				}
			}
			for(auto& current_row : level_rows){
				while(current_row.length() < max_length){
					current_row.append("D");
				}
			}
			levels_.emplace_back(level_rows);
		}
	}
	return true;
}

const std::vector<std::vector<std::string>>& ResourceManager::GetLevels(){
	return levels_;
}

std::shared_ptr<RenderEngine::Texture2D> ResourceManager::LoadTexture_atlas(const std::string& texture_name,
																		   const std::string& texture_path,
																		   const std::vector<std::string>& sub_textures_names,
																		   const uint32_t sub_texture_width,
																		   const uint32_t sub_texture_height){
	std::shared_ptr<RenderEngine::Texture2D> texture{LoadTexture(texture_name, texture_path)};
	if(texture){
		const uint32_t texture_width = texture->GetSize().width;
		const uint32_t texture_height = texture->GetSize().height;
		uint32_t current_texture_offset_x = 0;
		uint32_t current_texture_offset_y = texture_height;

		for(const auto& current_sub_texture_name : sub_textures_names){
			glm::vec2 left_bottom_UV{static_cast<float>(current_texture_offset_x + 0.01f) / texture_width,
				static_cast<float>(current_texture_offset_y - sub_texture_height + 0.01f) / texture_height};
			glm::vec2 right_top_UV{static_cast<float>(current_texture_offset_x + sub_texture_width - 0.01f) / texture_width,
				static_cast<float>(current_texture_offset_y - 0.01f) / texture_height};

			texture->Addsubtexture(current_sub_texture_name, left_bottom_UV, right_top_UV);

			current_texture_offset_x += sub_texture_width;

			if(current_texture_offset_x >= texture_width){
				current_texture_offset_x = 0;
				current_texture_offset_y -= sub_texture_height;
			}
		}
	}
	return texture;
}

std::string ResourceManager::GetFileString(const std::string& relative_path){
	std::ifstream ifs;
	ifs.open(path_ + '/' + relative_path.c_str(), std::ios::in | std::ios::binary);
	if(!ifs.is_open()){
		std::cerr << "Failed to open file: "sv << relative_path << std::endl;
		return std::string{};
	}

	std::stringstream buffer;
	buffer << ifs.rdbuf();
	return buffer.str();
}
