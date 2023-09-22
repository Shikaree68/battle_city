#include "level.h"

#include "../Resources/resource_manager.h"
#include"GameObjects/brick_wall.h"
#include<iostream>

const uint32_t BLOCK_SIZE = 16;

std::shared_ptr<GameObject> create_gameobject(const char description,
											  const glm::vec2& position,
											  const glm::vec2& size,
											  const float rotation){
	switch(description){
	case '0':
		return std::make_shared<BrickWall>(ResourceManager::GetSprite("brick_wall_right"), position, size, rotation);
	case '1':
		return std::make_shared<BrickWall>(ResourceManager::GetSprite("brick_wall_bottom"), position, size, rotation);
	case '2':
		return std::make_shared<BrickWall>(ResourceManager::GetSprite("brick_wall_left"), position, size, rotation);
	case '3':
		return std::make_shared<BrickWall>(ResourceManager::GetSprite("brick_wall_top"), position, size, rotation);
	case '4':
		return std::make_shared<BrickWall>(ResourceManager::GetSprite("brick_wall"), position, size, rotation);
	case '5':
		return std::make_shared<BrickWall>(ResourceManager::GetSprite("brick_wall"), position, size, rotation);
	case '6':
		return std::make_shared<BrickWall>(ResourceManager::GetSprite("brick_wall"), position, size, rotation);
	case '7':
		return std::make_shared<BrickWall>(ResourceManager::GetSprite("brick_wall"), position, size, rotation);
	case '8':
		return std::make_shared<BrickWall>(ResourceManager::GetSprite("brick_wall"), position, size, rotation);
	case '9':
		return std::make_shared<BrickWall>(ResourceManager::GetSprite("brick_wall"), position, size, rotation);
	case 'A':
		return std::make_shared<BrickWall>(ResourceManager::GetSprite("brick_wall"), position, size, rotation);
	case 'B':
		return std::make_shared<BrickWall>(ResourceManager::GetSprite("brick_wall"), position, size, rotation);
	case 'C':
		return std::make_shared<BrickWall>(ResourceManager::GetSprite("brick_wall"), position, size, rotation);
	case 'D':
		return nullptr;
	case 'E':
		return nullptr;
	case 'F':
		return std::make_shared<BrickWall>(ResourceManager::GetSprite("brick_wall"), position, size, rotation);
	case 'G':
		return std::make_shared<BrickWall>(ResourceManager::GetSprite("brick_wall"), position, size, rotation);
	case 'H':
		return std::make_shared<BrickWall>(ResourceManager::GetSprite("brick_wall"), position, size, rotation);
	case 'I':
		return std::make_shared<BrickWall>(ResourceManager::GetSprite("brick_wall"), position, size, rotation);
	case 'J':
		return std::make_shared<BrickWall>(ResourceManager::GetSprite("brick_wall"), position, size, rotation);
	default:
		std::cerr << "Unknown GameObject description: " << description << std::endl;;
	}
}

Level::Level(const std::vector<std::string>& level_description){
	if(level_description.empty()){
		std::cerr << "Empty level description!" << std::endl;
	}
	width_ = level_description[0].length();
	height_ = level_description.size();

	map_objects_.reserve(width_ * height_);
	uint32_t current_bottom_offset = BLOCK_SIZE * (height_ - 1);
	for(const std::string& current_row : level_description){
		uint32_t current_left_offset = 0;
		for(const char current_element:current_row){
			map_objects_.push_back(create_gameobject(current_element,
													 glm::vec2(current_left_offset, current_bottom_offset),
													 glm::vec2(BLOCK_SIZE, BLOCK_SIZE),
													 0.f));
			current_left_offset += BLOCK_SIZE;
		}
		current_bottom_offset -= BLOCK_SIZE;
	}
}

void Level::Render() const{
	for(const auto& current_map_obj : map_objects_){
		if(current_map_obj){
			current_map_obj->Render();
		}
	}
}

void Level::Update(const uint64_t delta){
	for(const auto& current_map_obj : map_objects_){
		if(current_map_obj){
			current_map_obj->Update(delta);
		}
	}
}
