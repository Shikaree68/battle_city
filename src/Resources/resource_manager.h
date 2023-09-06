#pragma once

#include <map>
#include <memory>
#include <string>
#include <vector>
namespace Renderer{
class ShaderProgram;
class Texture2D;
class Sprite;
class AnimatedSprite;
}  // namespace Renderer

class ResourceManager{
public:
	ResourceManager(const std::string& executable_path);
	~ResourceManager() = default;

	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;
	ResourceManager& operator=(ResourceManager&&) = delete;
	ResourceManager(ResourceManager&&) = delete;

	std::shared_ptr<Renderer::ShaderProgram> LoadShaders(const std::string& shader_name, 
														 const std::string& vertex_path,
														 const std::string& fragment_path);
	std::shared_ptr<Renderer::ShaderProgram> GetShaderProgram(const std::string& shader_name);

	std::shared_ptr<Renderer::Texture2D> LoadTexture(const std::string& texture_name, const std::string& texure_path);
	std::shared_ptr<Renderer::Texture2D> LoadTextureAtlas(const std::string& texture_name,
														  const std::string& texture_path, 
														  const std::vector<std::string>& sub_textures_names,
														  const uint32_t sub_texture_width, 
														  const uint32_t sub_texture_height);
	std::shared_ptr<Renderer::Texture2D> GetTexture(const std::string& texture_name);

	std::shared_ptr<Renderer::Sprite> LoadSprite(const std::string& sprite_name,
											   	 const std::string& texture_name,
											   	 const std::string& shader_name, 
											   	 const uint32_t sprite_width,
											   	 const uint32_t sprite_height, 
											   	 const std::string& sub_texture_name = "default");
	std::shared_ptr<Renderer::Sprite> GetSprite(const std::string& sprite_name);

	std::shared_ptr<Renderer::AnimatedSprite> LoadAnimatedSprite(const std::string& sprite_name,
											   	 const std::string& texture_name,
											   	 const std::string& shader_name, 
											   	 const uint32_t sprite_width,
											   	 const uint32_t sprite_height, 
											   	 const std::string& sub_texture_name = "default");
	std::shared_ptr<Renderer::AnimatedSprite> GetAnimatedSprite(const std::string& sprite_name);

private:
	typedef std::map<const std::string, std::shared_ptr<Renderer::ShaderProgram>> ShaderProgramsMap;
	typedef std::map<const std::string, std::shared_ptr<Renderer::Texture2D>> TexturesMap;
	typedef std::map<const std::string, std::shared_ptr<Renderer::Sprite>> SpritesMap;
	typedef std::map<const std::string, std::shared_ptr<Renderer::AnimatedSprite>> AnimatedSpritesMap;
	ShaderProgramsMap shader_programs_;
	std::string path_;
	TexturesMap textures_;
	SpritesMap sprites_;
	AnimatedSpritesMap animated_sprites_;

	std::string GetFileString(const std::string& relative_path) const;
};