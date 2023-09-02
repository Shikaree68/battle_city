#include "resource_manager.h"
#include "../Renderer/shader_program.h"

#include <sstream>
#include <fstream>
#include <iostream>

ResourceManager::ResourceManager(const std::string& executable_path)
{
	size_t found{executable_path.find_last_of("/\\")};
	path_ = executable_path.substr(0, found);
}

std::shared_ptr<Renderer::ShaderProgram> ResourceManager::LoadShaders(const std::string& shader_name, const std::string& vertex_path, const std::string& fragment_path)
{
	std::string vertex_string{ GetFileString(vertex_path) };
	if (vertex_string.empty()) {
		std::cerr << "No vertex shader!" << std::endl;
		return nullptr;
	}

	std::string fragment_string{ GetFileString(fragment_path) };
	if (fragment_string.empty()) {
		std::cerr << "No fragment shader!" << std::endl;
		return nullptr;
	}

	std::shared_ptr<Renderer::ShaderProgram>& new_shader{ 
		m_shader_programs_.emplace(shader_name, std::make_shared<Renderer::ShaderProgram>(vertex_string, fragment_string)).first->second };
	if (new_shader->IsCompiled()) {
		return new_shader;
	}
	std::cerr << "Can't load shader program:"
		<< "\nVertex: " << vertex_path
		<< "\nFragment: " << fragment_path
		<< std::endl;
	return nullptr;
}

std::shared_ptr<Renderer::ShaderProgram> ResourceManager::GetShaderProgram(const std::string& shader_name)
{
	ShaderProgramsMap::const_iterator it{ m_shader_programs_.find(shader_name) };
	if (it != m_shader_programs_.end()) {
		return it->second;
	}
	std::cerr << "Can't find the shader program: " << shader_name << std::endl;
	return nullptr;
}

std::string ResourceManager::GetFileString(const std::string& relative_path) const
{
	std::ifstream ifs;
	ifs.open(path_ + '/' + relative_path.c_str(), std::ios::in | std::ios::binary);
	if (!ifs.is_open())
	{
		std::cerr << "Failed to open file: " << relative_path << std::endl;
		return std::string{};
	}

	std::stringstream buffer;
	buffer << ifs.rdbuf();
	return buffer.str();
}
