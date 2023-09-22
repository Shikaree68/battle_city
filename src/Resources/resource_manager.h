#pragma once

#include <map>
#include <memory>
#include <string>
#include <vector>

namespace RenderEngine{
class ShaderProgram;
class Texture2D;
class Sprite;
class AnimatedSprite;
}  // namespace Renderer

class ResourceManager{
public:
	static void SetExecutablePath(const std::string& executable_path);
	static void UnloadAllResources();
	~ResourceManager() = delete;
	ResourceManager() = delete;
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;
	ResourceManager& operator=(ResourceManager&&) = delete;
	ResourceManager(ResourceManager&&) = delete;

	static std::shared_ptr<RenderEngine::ShaderProgram> LoadShaders(const std::string& shader_name,
																	const std::string& vertex_path,
																	const std::string& fragment_path);
	static std::shared_ptr<RenderEngine::ShaderProgram> GetShaderProgram(const std::string& shader_name);

	static std::shared_ptr<RenderEngine::Texture2D> LoadTexture(const std::string& texture_name, const std::string& texure_path);
	static std::shared_ptr<RenderEngine::Texture2D> LoadTextureAtlas(const std::string& texture_name,
																	 const std::string& texture_path,
																	 const std::vector<std::string>& sub_textures_names,
																	 const uint32_t sub_texture_width,
																	 const uint32_t sub_texture_height);
	static std::shared_ptr<RenderEngine::Texture2D> GetTexture(const std::string& texture_name);

	static std::shared_ptr<RenderEngine::Sprite> LoadSprite(const std::string& sprite_name,
															const std::string& texture_name,
															const std::string& shader_name,
															const std::string& sub_texture_name = "default");
	static std::shared_ptr<RenderEngine::Sprite> GetSprite(const std::string& sprite_name);

	static std::shared_ptr<RenderEngine::AnimatedSprite> LoadAnimatedSprite(const std::string& sprite_name,
																			const std::string& texture_name,
																			const std::string& shader_name,
																			const std::string& sub_texture_name = "default");
	static std::shared_ptr<RenderEngine::AnimatedSprite> GetAnimatedSprite(const std::string& sprite_name);

	static bool LoadJsonResources(const std::string& json_path);

	static const std::vector<std::vector<std::string>>& GetLevels();

private:
	typedef std::map<const std::string, std::shared_ptr<RenderEngine::ShaderProgram>> ShaderProgramsMap;
	typedef std::map<const std::string, std::shared_ptr<RenderEngine::Texture2D>> TexturesMap;
	typedef std::map<const std::string, std::shared_ptr<RenderEngine::Sprite>> SpritesMap;
	typedef std::map<const std::string, std::shared_ptr<RenderEngine::AnimatedSprite>> AnimatedSpritesMap;
	static ShaderProgramsMap shader_programs_;
	static std::string path_;
	static TexturesMap textures_;
	static SpritesMap sprites_;
	static AnimatedSpritesMap animated_sprites_;
	static std::vector<std::vector<std::string>> levels_;

	static std::string GetFileString(const std::string& relative_path);
};