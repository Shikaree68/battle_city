#include "game.h"
#include "./GameObjects/tank.h"
#include "./GameObjects/bullet.h"

#include "../Renderer/shader_program.h"
#include "../Resources/resource_manager.h"
#include "../Renderer/texture_2D.h"
#include "../Renderer/sprite.h"
#include "../Renderer/renderer.h"
#include "../Physics/physics_engine.h"

#include "GameStates/level.h"
#include "GameStates/start_screen.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>

using namespace std::literals;

Game::Game(const glm::uvec2& window_size)
	: state_(State::StartScreen)
	, window_size_(window_size) {
	keys_.fill(false);
}

Game::~Game() {}

void Game::Render() {
	game_state_->Render();
}

void Game::Update(double delta) {
	game_state_->ProcessInput(keys_);
	game_state_->Update(delta);
	//switch (state_) {
	//case Game::State::StartScreen:
	//	if (keys_[GLFW_KEY_ENTER]) {
	//		state_ = State::Level;
	//		StartNewLevel(0);
	//	}
	//	break;
	//case Game::State::Level:
	//	break;
	//}
};

void Game::SetKey(int key, int action) {
	keys_[key] = action;
}

bool Game::Initialize() {
	ResourceManager::LoadJsonResources("res/resources.json"s);
	sprite_shader_program_ = ResourceManager::GetShaderProgram("sprite_shader"s);
	if(!sprite_shader_program_) {
		std::cerr << "Can't find shader program: "sv << "sprite_shader"sv << std::endl;
		return false;
	}
	sprite_shader_program_->Use();
	sprite_shader_program_->SetInt("tex"s, 0);
	game_state_ = std::make_shared<StartScreen>(ResourceManager::GetStartScreen(), this);
	SetWindowSize(window_size_);
	UpdateViewport();	
	return true;
}

void Game::StartNewLevel(std::size_t level) {
	auto new_level = std::make_shared<Level>(ResourceManager::GetLevels()[level]);
	game_state_ = new_level;
	Physics::PhysicsEngine::SetCurrentLevel(new_level);	
	UpdateViewport();
}

dimension_t Game::GetCurrentWidth() const {
	return game_state_->GetStateWidth();
}

dimension_t Game::GetCurrentHeight() const {
	return game_state_->GetStateHeight();
}

void Game::SetWindowSize(const glm::uvec2 &window_size) {
	window_size_ = window_size;
	UpdateViewport();
}

void Game::UpdateViewport() const {
	const float level_aspect_ratio = static_cast<float>(GetCurrentWidth()) / GetCurrentHeight();
	std::uint32_t view_port_width = window_size_.x;
	std::uint32_t view_port_height = window_size_.y;
	std::uint32_t view_port_left_offset = 0;
	std::uint32_t view_port_bottom_offset = 0;

	if (window_size_.x * 1.f / window_size_.y > level_aspect_ratio) {
		view_port_width = static_cast<uint32_t>(window_size_.y * level_aspect_ratio);
		view_port_left_offset = (window_size_.x - view_port_width) / 2;
	} else {
		view_port_height = static_cast<uint32_t>(window_size_.x / level_aspect_ratio);
		view_port_bottom_offset = (window_size_.y - view_port_height) / 2;
	}

	RenderEngine::Renderer::SetViewport(view_port_width, view_port_height, view_port_left_offset, view_port_bottom_offset);
	glm::mat4 projection_matrix = glm::ortho(0.f, static_cast<float>(GetCurrentWidth()),
											 0.f, static_cast<float>(GetCurrentWidth()),
											 -100.f, 100.f);
	sprite_shader_program_->SetMatrix4("projection_matrix"s, projection_matrix);
}
