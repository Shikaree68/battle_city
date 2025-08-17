#include "game.h"
#include "./GameObjects/tank.h"
#include "./GameObjects/bullet.h"

#include "../Renderer/shader_program.h"
#include "../Resources/resource_manager.h"
#include "../Renderer/texture_2D.h"
#include "../Renderer/sprite.h"
#include "../Physics/physics_engine.h"

#include "GameStates/level.h"
#include "GameStates/start_screen.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>

using namespace std::literals;

Game::Game(const glm::ivec2& window_size)
	: state_(GameState::StartScreen)
	, window_size_(window_size) {
	keys_.fill(false);
}

Game::~Game() {}

void Game::Render() {
	switch (state_) {
	case Game::GameState::StartScreen:
		start_screen_->Render();
		break;
	case Game::GameState::Level:
		if (tank_) {
			tank_->Render();
		}
		if (level_) {
			level_->Render();
		}
		break;
	}
}

void Game::Update(double delta) {
	switch (state_) {
	case Game::GameState::StartScreen:
		if (keys_[GLFW_KEY_ENTER]) {
			state_ = GameState::Level;
		}
		break;
	case Game::GameState::Level:
		if (level_) {
			level_->Update(delta);
		}
		if (tank_) {
			if (keys_[GLFW_KEY_W]) {
				tank_->SetOrientation(Tank::Orientation::Top);
				tank_->SetVelocity(tank_->GetMaxVelocity());
			} else if (keys_[GLFW_KEY_A]) {
				tank_->SetOrientation(Tank::Orientation::Left);
				tank_->SetVelocity(tank_->GetMaxVelocity());
			} else if (keys_[GLFW_KEY_D]) {
				tank_->SetOrientation(Tank::Orientation::Right);
				tank_->SetVelocity(tank_->GetMaxVelocity());
			} else if (keys_[GLFW_KEY_S]) {
				tank_->SetOrientation(Tank::Orientation::Bottom);
				tank_->SetVelocity(tank_->GetMaxVelocity());
			} else {
				tank_->SetVelocity(0);
			}
			if (tank_ && keys_[GLFW_KEY_SPACE]) {
				tank_->Fire();
			}
			tank_->Update(delta);
		}
		break;
	}
};

void Game::SetKey(int key, int action) {
	keys_[key] = action;
}

bool Game::Initialize() {
	ResourceManager::LoadJsonResources("res/resources.json"s);
	auto sprite_shader_program = ResourceManager::GetShaderProgram("sprite_shader"s);
	if(!sprite_shader_program) {
		std::cerr << "Can't find shader program: "sv << "sprite_shader"sv << std::endl;
		return false;
	}
	start_screen_ = std::make_shared<StartScreen>(ResourceManager::GetStartScreen());
	level_ = std::make_shared<Level>(ResourceManager::GetLevels()[0]);
	window_size_.x = static_cast<int>(level_->GetStateWidth());
	window_size_.y = static_cast<int>(level_->GetStateHeight());
	Physics::PhysicsEngine::SetCurrentLevel(level_);

	glm::mat4 projection_matrix = glm::ortho(0.f, static_cast<float>(window_size_.x),
											 0.f, static_cast<float>(window_size_.y),
											 -100.f, 100.f);

	sprite_shader_program->Use();
	sprite_shader_program->SetInt("tex"s, 0);
	sprite_shader_program->SetMatrix4("projection_matrix"s, projection_matrix);

	tank_ = std::make_shared<Tank>(0.05f, level_->GetPlayerRespawn_1(), glm::vec2(Level::BLOCK_SIZE, Level::BLOCK_SIZE), 0.f);
	Physics::PhysicsEngine::AddDynamicGameObject(tank_);
	return true;
}

dimension_t Game::GetCurrentWidth() const {
	switch (state_) {
	case Game::GameState::StartScreen:
		return start_screen_->GetStateWidth();
	case Game::GameState::Level:
		return level_->GetStateWidth();
	}
}

dimension_t Game::GetCurrentHeight() const {
	switch (state_) {
	case Game::GameState::StartScreen:
		return start_screen_->GetStateHeight();
	case Game::GameState::Level:
		return level_->GetStateHeight();
	}
}
