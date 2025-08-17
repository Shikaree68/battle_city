#pragma once

#include "start_screen.h"

#include <iostream>

#include "../../Resources/resource_manager.h"
#include "../../Renderer/sprite.h"

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


StartScreen::StartScreen(const std::vector<std::string> &start_screen_description) {
	if (start_screen_description.empty()) {
		std::cerr << "Empty start screen description!" << std::endl;
	}

	auto left_offset_pixels = 2 * BLOCK_SIZE;
	auto bottom_offset = STARTSCREEN_HEIGHT - 2 * BLOCK_SIZE;

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
}
void StartScreen::Update(double delta) {

}
std::uint32_t StartScreen::GetStateWidth() const {
	return STARTSCREEN_WIDTH;
}
std::uint32_t StartScreen::GetStateHeight() const {
	return STARTSCREEN_HEIGHT;
}
