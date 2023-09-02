#pragma once

#include <string>
#include <memory>
#include <map>
namespace Renderer 
{
	class ShaderProgram;
}

class ResourceManager {
public:
	ResourceManager(const std::string& executable_path);
	~ResourceManager() = default;

	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;
	ResourceManager& operator=(ResourceManager&&) = delete;
	ResourceManager(ResourceManager&&) = delete;

	std::shared_ptr<Renderer::ShaderProgram> LoadShaders(const std::string& shader_name, const std::string& vertex_path, const std::string& fragment_path);
	std::shared_ptr<Renderer::ShaderProgram> GetShaderProgram(const std::string& shader_name);

private:
	typedef std::map<const std::string, std::shared_ptr<Renderer::ShaderProgram>> ShaderProgramsMap;
	ShaderProgramsMap m_shader_programs_;
	std::string path_;

	std::string GetFileString(const std::string& relative_path) const;
};