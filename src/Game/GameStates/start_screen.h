#pragma once



#include "game_state.h"
#include "../../Renderer/sprite_animator.h"

#include <vector>
#include <string>
#include <memory>
#include <utility>
#include <glm/vec2.hpp>

namespace RenderEngine {
class Sprite;
}

class Game;

class StartScreen : public GameState {
public:
	static constexpr std::uint32_t BLOCK_SIZE = 8;
	static constexpr std::uint32_t STARTSCREEN_WIDTH = 15 * BLOCK_SIZE * 2;
	static constexpr std::uint32_t STARTSCREEN_HEIGHT = 14 * BLOCK_SIZE * 2;
	static constexpr std::uint32_t MENU_WIDTH = 128;
	static constexpr std::uint32_t MENU_HEIGHT = 64;
	static constexpr std::uint32_t TANK_SIZE = BLOCK_SIZE * 2;

	StartScreen(const std::vector<std::string> &start_screen_description, Game* game);
	virtual void Render() const;
	virtual void Update(double delta);
	virtual void ProcessInput(const std::array<bool, 349> &keys) override;
	virtual std::uint32_t GetStateWidth() const;
	virtual std::uint32_t GetStateHeight() const;
private:
	Game *game_;
	std::int32_t current_menu_selection_;
	std::vector<std::pair<std::shared_ptr<RenderEngine::Sprite>, glm::vec2>> sprites_;
	std::pair<std::shared_ptr<RenderEngine::Sprite>, glm::vec2> menu_sprite_;
	std::pair<std::shared_ptr<RenderEngine::Sprite>, glm::vec2> tank_sprite_;
	RenderEngine::SpriteAnimator tank_sprite_animator_;
	bool key_released_;
};

