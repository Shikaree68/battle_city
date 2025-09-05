#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include "start_screen.h"

#include <iostream>

#include "../../Resources/resource_manager.h"
#include "../../Renderer/sprite.h"
#include "../game.h"

static std::shared_ptr<RenderEngine::Sprite> GetSpriteForDescription(char description) {
	switch (description) {
	case '0':
		return ResourceManager::GetSprite("brick_all");
	case '1':
		return ResourceManager::GetSprite("brick_top_left");
	case '2':
		return ResourceManager::GetSprite("brick_top_right");
	case '3':
		return ResourceManager::GetSprite("brick_top");
	case '4':
		return ResourceManager::GetSprite("brick_bottom_left");
	case '5':
		return ResourceManager::GetSprite("brick_left");
	case '6':
		return ResourceManager::GetSprite("brick_top_right_bottom_left");
	case '7':
		return ResourceManager::GetSprite("brick_top_bottom_left");
	case '8':
		return ResourceManager::GetSprite("brick_bottom_right");
	case '9':
		return ResourceManager::GetSprite("brick_top_left_bottom_right");
	case 'A':
		return ResourceManager::GetSprite("brick_right");
	case 'B':
		return ResourceManager::GetSprite("brick_top_bottom_right");
	case 'C':
		return ResourceManager::GetSprite("brick_bottom");
	case 'D':
		return ResourceManager::GetSprite("brick_top_left_bottom");
	case 'E':
		return ResourceManager::GetSprite("brick_top_right_bottom");
	case 'F':
		return nullptr;
	default:
		std::cerr << "Unknown Start Level description: " << description << std::endl;
	}
	return nullptr;
}


StartScreen::StartScreen(const std::vector<std::string> &start_screen_description, Game *game)
	: game_(game)
	, current_menu_selection_(0)
	, menu_sprite_(std::make_pair(ResourceManager::GetSprite("menu"), glm::vec2(11 * BLOCK_SIZE, STARTSCREEN_HEIGHT - start_screen_description.size() * BLOCK_SIZE - MENU_HEIGHT - 5 * BLOCK_SIZE)))
	, tank_sprite_(std::make_pair(ResourceManager::GetSprite("tank_right_state"), glm::vec2(8 * BLOCK_SIZE, menu_sprite_.second.y + 6 * BLOCK_SIZE  - 2 * current_menu_selection_ * BLOCK_SIZE)))
	, tank_sprite_animator_(tank_sprite_.first)
	, key_released_(true) {
	if (start_screen_description.empty()) {
		std::cerr << "Empty start screen description!" << std::endl;
	}

	auto left_offset_pixels = 4 * BLOCK_SIZE;
	auto bottom_offset = STARTSCREEN_HEIGHT - 4 * BLOCK_SIZE;

	std::uint32_t current_bottom_offset = bottom_offset;
	for (const std::string &current_row : start_screen_description) {
		std::uint32_t current_left_offset = left_offset_pixels;
		for (char element : current_row) {
			sprites_.emplace_back(std::make_pair(GetSpriteForDescription(element), glm::vec2(current_left_offset, current_bottom_offset)));
			current_left_offset += BLOCK_SIZE;
		}
		current_bottom_offset -= BLOCK_SIZE;
	}

}
void StartScreen::Render() const {
	for (const auto &sprite : sprites_) {
		if (sprite.first) {
			sprite.first->Render(sprite.second, glm::vec2(BLOCK_SIZE), 0.f);
		}
	}
	menu_sprite_.first->Render(menu_sprite_.second, glm::vec2(MENU_WIDTH, MENU_HEIGHT), 0);
	tank_sprite_.first->Render(glm::vec2(tank_sprite_.second.x, tank_sprite_.second.y - current_menu_selection_ * 2 * BLOCK_SIZE), glm::vec2(TANK_SIZE), 0.f, 0.f, tank_sprite_animator_.GetCurrentFrame());
}
void StartScreen::Update(double delta) {
	tank_sprite_animator_.Update(delta);
}
void StartScreen::ProcessInput(const std::array<bool, 349> &keys) {
	if (!keys[GLFW_KEY_W] && !keys[GLFW_KEY_S]) {
		key_released_ = true;
	}
	if (key_released_) {
		if (keys[GLFW_KEY_W]) {
			key_released_ = false;
			--current_menu_selection_;
			if (current_menu_selection_ < 0) {
				current_menu_selection_ = 2;
			}
		} else if (keys[GLFW_KEY_S]) {
			key_released_ = false;
			++current_menu_selection_;
			if (current_menu_selection_ > 2) {
				current_menu_selection_ = 0;
			}
		}
	}
	if (keys[GLFW_KEY_ENTER]) {
		switch (current_menu_selection_) {
		case 0 :
			game_->StartNewLevel(0);
		default:
			break;
		}
	}
}
std::uint32_t StartScreen::GetStateWidth() const {
	return STARTSCREEN_WIDTH;
}
std::uint32_t StartScreen::GetStateHeight() const {
	return STARTSCREEN_HEIGHT;
}
