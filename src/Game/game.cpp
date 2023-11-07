#include "game.h"
#include "./GameObjects/tank.h"

#include "../Renderer/shader_program.h"
#include "../Resources/resource_manager.h"
#include "../Renderer/texture_2D.h"
#include "../Renderer/sprite.h"
#include "level.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>

using namespace std::literals;

Game::Game(const glm::ivec2& window_size)
	: current_state_(GameState::Active)
	, window_size_(window_size){
	keys_.fill(false);
}

Game::~Game(){}

void Game::Render(){
	if(tank_){
		tank_->Render();
	}
	if(level_){
		level_->Render();
	}
}

void Game::Update(const double delta){
	if(level_){
		level_->Update(delta);
	}
	if(tank_){
		if(keys_[GLFW_KEY_W]){
			tank_->SetOrientation(Tank::Orientation::Top);
			tank_->Move(true);
		} else if(keys_[GLFW_KEY_A]){
			tank_->SetOrientation(Tank::Orientation::Left);
			tank_->Move(true);
		} else if(keys_[GLFW_KEY_D]){
			tank_->SetOrientation(Tank::Orientation::Right);
			tank_->Move(true);
		} else if(keys_[GLFW_KEY_S]){
			tank_->SetOrientation(Tank::Orientation::Bottom);
			tank_->Move(true);
		} else{
			tank_->Move(false);
		}
		tank_->Update(delta);
	}
};

void Game::SetKey(const int key, int action){
	keys_[key] = action;
}

bool Game::Initialize(){
	ResourceManager::LoadJsonResources("res/resources.json"s);
	auto sprite_shader_program = ResourceManager::GetShaderProgram("sprite_shader"s);
	if(!sprite_shader_program){
		std::cerr << "Can't find shader program: "sv << "sprite_shader"sv << std::endl;
		return false;
	}
	level_ = std::make_unique<Level>(ResourceManager::GetLevels()[1]);
	window_size_.x = static_cast<int>(level_->GetLevelWidth());
	window_size_.y = static_cast<int>(level_->GetLevelHeight());
	glm::mat4 projection_matrix = glm::ortho(0.f, static_cast<float>(window_size_.x),
											0.f, static_cast<float>(window_size_.y),
											-100.f, 100.f);

	sprite_shader_program->Use();
	sprite_shader_program->SetInt("tex"s, 0);
	sprite_shader_program->SetMatrix4("projection_matrix"s, projection_matrix);

	tank_ = std::make_unique<Tank>(0.05f, level_->GetPlayerRespawn_1(), glm::vec2(Level::BLOCK_SIZE, Level::BLOCK_SIZE), 0.f);

	return true;
}

size_t Game::GetCurrentLevelWidth() const {
	return level_->GetLevelWidth();
}

size_t Game::GetCurrentLevelHeight() const {
	return level_->GetLevelHeight();
}
