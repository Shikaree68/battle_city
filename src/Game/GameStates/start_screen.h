#pragma once



#include "game_state.h"

#include <vector>
#include <string>
#include <memory>
#include <utility>
#include <glm/vec2.hpp>

namespace RenderEngine {
class Sprite;
}

class StartScreen : public GameState {
public:
	static constexpr std::uint32_t BLOCK_SIZE = 8;
	static constexpr std::uint32_t STARTSCREEN_WIDTH = 15 * BLOCK_SIZE * 2;
	static constexpr std::uint32_t STARTSCREEN_HEIGHT = 14 * BLOCK_SIZE * 2;

	StartScreen(const std::vector<std::string> &start_screen_description);
	virtual void Render() const;
	virtual void Update(double delta);
	virtual std::uint32_t GetStateWidth() const;
	virtual std::uint32_t GetStateHeight() const;
private:
	std::vector<std::pair<std::shared_ptr<RenderEngine::Sprite>, glm::vec2>> sprites_;
};

