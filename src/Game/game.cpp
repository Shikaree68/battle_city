#include "game.h"
#include "./GameObjects/tank.h"

#include "../Renderer/shader_program.h"
#include "../Resources/resource_manager.h"
#include "../Renderer/texture_2D.h"
#include "../Renderer/sprite.h"
#include "../Renderer/animated_sprite.h"
#include "level.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>

Game::Game(const glm::ivec2& window_size)
	: current_state_(GameState::Active)
	, window_size_(window_size){
	keys_.fill(false);
}

Game::~Game(){}

void Game::Render(){
	//ResourceManager::GetAnimatedSprite("NewAnimatedSprite")->Render();
	if(level_){
		level_->Render();
	}
	if(tank_){
		tank_->Render();
	}
}

void Game::Update(const uint64_t delta){
	//ResourceManager::GetAnimatedSprite("NewAnimatedSprite")->Update(delta);
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
	ResourceManager::LoadJsonResources("res/resources.json");
	auto sprite_shader_program = ResourceManager::GetShaderProgram("sprite_shader");
	if(!sprite_shader_program){
		std::cerr << "Can't find shader porgram: " << "sprite_shader" << std::endl;
		return false;
	}

	auto map_texture_atlas = ResourceManager::GetTexture("map_texture_atlas");
	if(!map_texture_atlas){
		std::cerr << "Can't find texture atlas: " << "map_texture_atlas" << std::endl;
		return false;
	}

	auto tanks_texture_atlas = ResourceManager::GetTexture("tanks_texture_atlas");
	if(!tanks_texture_atlas){
		std::cerr << "Can't find texture atlas: " << "tanks_texture_atlas" << std::endl;
		return false;
	}


	auto animated_sprite = ResourceManager::LoadAnimatedSprite("NewAnimatedSprite",
															   "tanks_texture_atlas",
															   "sprite_shader",
															   "block");

	std::vector<std::pair<std::string, uint64_t>> water_state;
	water_state.emplace_back(std::make_pair<std::string, uint64_t>("water1", 1'000'000'000));
	water_state.emplace_back(std::make_pair<std::string, uint64_t>("water2", 1'000'000'000));
	water_state.emplace_back(std::make_pair<std::string, uint64_t>("water3", 1'000'000'000));

	std::vector<std::pair<std::string, uint64_t>> eagle_state;
	eagle_state.emplace_back(std::make_pair<std::string, uint64_t>("eagle", 1'000'000'000));
	eagle_state.emplace_back(std::make_pair<std::string, uint64_t>("dead_eagle", 1'000'000'000));

	animated_sprite->InsertState("water_state", water_state);
	animated_sprite->InsertState("eagle_state", eagle_state);

	animated_sprite->SetState("water_state");

	glm::mat4 pojection_matrix = glm::ortho(0.f, static_cast<float>(window_size_.x),
											0.f, static_cast<float>(window_size_.y),
											-100.f, 100.f);


	sprite_shader_program->Use();
	sprite_shader_program->SetInt("tex", 0);
	sprite_shader_program->SetMatrix4("projection_matrix", pojection_matrix);

	auto tank_animated_sprite = ResourceManager::GetAnimatedSprite("tank_animated_sprite");
	if(!tank_animated_sprite){
		std::cerr << "Can't find texture atlas: " << "tanks_texture_atlas" << std::endl;
		return false;
	}
	tank_ = std::make_unique<Tank>(tank_animated_sprite, 0.0000001f, glm::vec2(0), glm::vec2(16.f, 16.f));

	level_ = std::make_unique<Level>(ResourceManager::GetLevels()[0]);
	return true;
}
