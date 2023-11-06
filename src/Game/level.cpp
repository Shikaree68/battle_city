#include "level.h"

#include"GameObjects/brick_wall.h"
#include"GameObjects/beton_wall.h"
#include"GameObjects/trees.h"
#include"GameObjects/ice.h"
#include"GameObjects/water.h"
#include"GameObjects/eagle.h"

#include<iostream>

using namespace std::literals;

const uint32_t BLOCK_SIZE = 16;

std::shared_ptr<GameObject> create_gameobject(const char description,
											  const glm::vec2& position,
											  const glm::vec2& size,
											  const float rotation) {
	switch(description) {
	case '0':
		return std::make_shared<BrickWall>(BrickWall::Type::Right, position, size, rotation, 0.f);
	case '1':
		return std::make_shared<BrickWall>(BrickWall::Type::Bottom, position, size, rotation, 0.f);
	case '2':
		return std::make_shared<BrickWall>(BrickWall::Type::Left, position, size, rotation, 0.f);
	case '3':
		return std::make_shared<BrickWall>(BrickWall::Type::Top, position, size, rotation, 0.f);
	case '4':
		return std::make_shared<BrickWall>(BrickWall::Type::All, position, size, rotation, 0.f);
	case '5':
		return std::make_shared<BetonWall>(BetonWall::Type::Right, position, size, rotation, 0.f);
	case '6':
		return std::make_shared<BetonWall>(BetonWall::Type::Bottom, position, size, rotation, 0.f);
	case '7':
		return std::make_shared<BetonWall>(BetonWall::Type::Left, position, size, rotation, 0.f);
	case '8':
		return std::make_shared<BetonWall>(BetonWall::Type::Top, position, size, rotation, 0.f);
	case '9':
		return std::make_shared<BetonWall>(BetonWall::Type::All, position, size, rotation, 0.f);
	case 'A':
		return std::make_shared<Water>( position, size, rotation, 0.f);
	case 'B':
		return std::make_shared<Trees>(position, size, rotation, 1.f);
	case 'C':
		return std::make_shared<Ice>(position, size, rotation, -1.f);
	case 'D':
		return nullptr;
	case 'E':
		return std::make_shared<Eagle>(position, size, rotation, 0.f);
		/*
		case 'F':
			return std::make_shared<BrickWall>(ResourceManager::GetSprite("brick_wall"), position, size, rotation);
			*/
	case 'G':
		return std::make_shared<BrickWall>(BrickWall::Type::BottomLeft, position, size, rotation, 0.f);
	case 'H':
		return std::make_shared<BrickWall>(BrickWall::Type::BottomRight, position, size, rotation, 0.f);
	case 'I':
		return std::make_shared<BrickWall>(BrickWall::Type::TopLeft, position, size, rotation, 0.f);
	case 'J':
		return std::make_shared<BrickWall>(BrickWall::Type::TopRight, position, size, rotation, 0.f);
	default:
		std::cerr << "Unknown GameObject description: "sv << description << std::endl;
		return nullptr;
	}
}

Level::Level(const std::vector<std::string>& level_description) {
	if(level_description.empty()) {
		std::cerr << "Empty level description!"sv << std::endl;
	}
	width_ = level_description[0].length();
	height_ = level_description.size();

	map_objects_.reserve(width_ * height_);
	uint64_t current_bottom_offset = BLOCK_SIZE * (height_ - 1);
	for(const std::string& current_row : level_description) {
		uint64_t current_left_offset = 0;
		for(const char current_element : current_row) {
			map_objects_.push_back(create_gameobject(current_element,
													 glm::vec2(current_left_offset, current_bottom_offset),
													 glm::vec2(BLOCK_SIZE, BLOCK_SIZE),
													 0.f));
			current_left_offset += BLOCK_SIZE;
		}
		current_bottom_offset -= BLOCK_SIZE;
	}
}

void Level::Render() const {
	for(const auto& current_map_obj : map_objects_) {
		if(current_map_obj) {
			current_map_obj->Render();
		}
	}
}

void Level::Update(const uint64_t delta) {
	for(const auto& current_map_obj : map_objects_) {
		if(current_map_obj) {
			current_map_obj->Update(delta);
		}
	}
}
