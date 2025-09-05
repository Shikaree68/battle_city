#include "level.h"

#include "../GameObjects/brick_wall.h"
#include "../GameObjects/beton_wall.h"
#include "../GameObjects/trees.h"
#include "../GameObjects/ice.h"
#include "../GameObjects/water.h"
#include "../GameObjects/eagle.h"
#include "../GameObjects/border.h"
#include "../GameObjects/tank.h"

#include <GLFW/glfw3.h>
#include <iostream>
#include <algorithm>

using namespace std::literals;

std::shared_ptr<GameObject> create_gameobject_from_description(const char description,
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
		return std::make_shared<Water>(position, size, rotation, 0.f);
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
	width_in_blocks_ = static_cast<uint32_t>(level_description[0].length());
	height_in_blocks_ = static_cast<uint32_t>(level_description.size());
	width_in_pixels_ = static_cast<uint64_t>(width_in_blocks_) * BLOCK_SIZE;
	height_in_pixels_ = static_cast<uint64_t>(height_in_blocks_) * BLOCK_SIZE;

	player_respawn_1_ = {width_in_pixels_ / 2 - BLOCK_SIZE, BLOCK_SIZE / 2};
	player_respawn_2_ = {width_in_pixels_ / 2 + 3 * BLOCK_SIZE, BLOCK_SIZE / 2};
	enemy_respawn_1_ = {BLOCK_SIZE, height_in_pixels_ - BLOCK_SIZE / 2};
	enemy_respawn_1_ = {width_in_pixels_ / 2 + BLOCK_SIZE, height_in_pixels_ - BLOCK_SIZE / 2};
	enemy_respawn_1_ = {width_in_pixels_, height_in_pixels_ - BLOCK_SIZE / 2};

	level_objects_.reserve(static_cast<uint64_t>(width_in_blocks_ * height_in_blocks_ + 4));
	uint64_t current_bottom_offset = height_in_pixels_ - BLOCK_SIZE / 2;
	for(const std::string& current_row : level_description) {
		uint64_t current_left_offset = BLOCK_SIZE;
		for(const char current_element : current_row) {
			switch(current_element) {
			case'K':
				player_respawn_1_ = {current_left_offset, current_bottom_offset};
				level_objects_.push_back(nullptr);
				break;
			case'L':
				player_respawn_2_ = {current_left_offset, current_bottom_offset};
				level_objects_.push_back(nullptr);
				break;
			case'M':
				enemy_respawn_1_ = {current_left_offset, current_bottom_offset};
				level_objects_.push_back(nullptr);
				break;
			case'N':
				enemy_respawn_2_ = {current_left_offset, current_bottom_offset};
				level_objects_.push_back(nullptr);
				break;
			case'O':
				enemy_respawn_3_ = {current_left_offset, current_bottom_offset};
				level_objects_.push_back(nullptr);
				break;
			default:
				level_objects_.push_back(
					create_gameobject_from_description(current_element,
													   glm::vec2(current_left_offset, current_bottom_offset),
													   glm::vec2(BLOCK_SIZE, BLOCK_SIZE), 0.f));
				break;
			}


			current_left_offset += BLOCK_SIZE;
		}
		current_bottom_offset -= BLOCK_SIZE;
	}
	//bottom border
	level_objects_.push_back(std::make_shared<Border>(glm::vec2(BLOCK_SIZE, 0.f),
													  glm::vec2(width_in_pixels_, BLOCK_SIZE / 2.f),
													  0.f, 0.f));
	//top_border
	level_objects_.push_back(std::make_shared<Border>(glm::vec2(BLOCK_SIZE, height_in_pixels_ + BLOCK_SIZE / 2.f),
													  glm::vec2(width_in_pixels_, BLOCK_SIZE / 2.f),
													  0.f, 0.f));
	//left_border
	level_objects_.push_back(std::make_shared<Border>(glm::vec2(0.f, 0.f),
													  glm::vec2(BLOCK_SIZE, height_in_pixels_ + BLOCK_SIZE),
													  0.f, 0.f));
	//right_border
	level_objects_.push_back(std::make_shared<Border>(glm::vec2(width_in_pixels_ + BLOCK_SIZE, 0.f),
													  glm::vec2(BLOCK_SIZE * 2.f, height_in_pixels_ + BLOCK_SIZE),
													  0.f, 0.f));

}

void Level::Render() const {
	for(const auto& current_map_obj : level_objects_) {
		if(current_map_obj) {
			current_map_obj->Render();
		}
	}
	tank_->Render();
}

void Level::Update(const double delta) {
	for(const auto& current_map_obj : level_objects_) {
		if(current_map_obj) {
			current_map_obj->Update(delta);
		}
	}
	tank_->Update(delta);
}
void Level::ProcessInput(const std::array<bool, 349> &keys) {
	if (keys[GLFW_KEY_W]) {
		tank_->SetOrientation(Tank::Orientation::Top);
		tank_->SetVelocity(tank_->GetMaxVelocity());
	} else if (keys[GLFW_KEY_A]) {
		tank_->SetOrientation(Tank::Orientation::Left);
		tank_->SetVelocity(tank_->GetMaxVelocity());
	} else if (keys[GLFW_KEY_D]) {
		tank_->SetOrientation(Tank::Orientation::Right);
		tank_->SetVelocity(tank_->GetMaxVelocity());
	} else if (keys[GLFW_KEY_S]) {
		tank_->SetOrientation(Tank::Orientation::Bottom);
		tank_->SetVelocity(tank_->GetMaxVelocity());
	} else {
		tank_->SetVelocity(0);
	}
	if (tank_ && keys[GLFW_KEY_SPACE]) {
		tank_->Fire();
	}
}
std::uint32_t Level::GetStateWidth() const {
	return static_cast<std::uint32_t>((width_in_blocks_ + 3) * BLOCK_SIZE);
}
std::uint32_t Level::GetStateHeight() const {
	return static_cast<std::uint32_t>((height_in_blocks_ + 1) * BLOCK_SIZE);
}

std::vector<std::shared_ptr<GameObject>> Level::GetObjectsInArea(const glm::vec2 bottom_left,
																 const glm::vec2 top_right) const {
	std::vector<std::shared_ptr<GameObject>> output;
	output.reserve(9);

	glm::vec2 bottom_left_converted(std::clamp(bottom_left.x - BLOCK_SIZE, 0.f, static_cast<float>(width_in_pixels_)),
									std::clamp(height_in_pixels_ - bottom_left.y + BLOCK_SIZE / 2,
											   0.f, static_cast<float>(height_in_pixels_)));
	glm::vec2 top_right_converted(std::clamp(top_right.x - BLOCK_SIZE, 0.f, static_cast<float>(width_in_pixels_)),
								  std::clamp(height_in_pixels_ - top_right.y + BLOCK_SIZE / 2,
											 0.f, static_cast<float>(height_in_pixels_)));

	size_t start_x = static_cast<size_t>(std::floor(bottom_left_converted.x / BLOCK_SIZE));
	size_t end_x = static_cast<size_t>(std::ceil(top_right_converted.x / BLOCK_SIZE));

	size_t start_y = static_cast<size_t>(std::floor(top_right_converted.y / BLOCK_SIZE));
	size_t end_y = static_cast<size_t>(std::ceil(bottom_left_converted.y / BLOCK_SIZE));

	for(size_t column = start_x; column < end_x; ++column) {
		for(size_t row = start_y; row < end_y; ++row) {
			auto& object = level_objects_[row * width_in_blocks_ + column];
			if(object) {
				output.push_back(object);
			}
		}
	}
	if(end_x >= width_in_blocks_) {
		output.push_back(level_objects_[level_objects_.size() - 1]);
	}
	if(start_x <= 1) {
		output.push_back(level_objects_[level_objects_.size() - 2]);
	}
	if(start_y <= 1) {
		output.push_back(level_objects_[level_objects_.size() - 3]);
	}
	if(end_y >= height_in_blocks_) {
		output.push_back(level_objects_[level_objects_.size() - 4]);
	}
	return output;
}

void Level::InitPhysics() {
	tank_ = std::make_shared<Tank>(0.05f, GetPlayerRespawn_1(), glm::vec2(Level::BLOCK_SIZE, Level::BLOCK_SIZE), 0.f);
	Physics::PhysicsEngine::AddDynamicGameObject(tank_);
}
