#pragma once

#include <array>
#include <memory>
#include <glm/vec2.hpp>

class GameState;

namespace RenderEngine {
class ShaderProgram;
}

using dimension_t = std::uint32_t;

class Game {
public:
	Game(const glm::uvec2& window_size);
	~Game();

	void Render();
	void Update(double delta);
	void SetKey(int key, int action);
	bool Initialize();
	void StartNewLevel(std::size_t level);
	dimension_t GetCurrentWidth() const;
	dimension_t GetCurrentHeight() const;
	void SetWindowSize(const glm::uvec2 &window_size);
	void UpdateViewport() const;
private:
	enum class State {
		StartScreen,
		LevelStart,
		Level,
		Pause,
		Scores,
		GameOver
	};

	std::array<bool, 349> keys_;

	State state_;
	glm::ivec2 window_size_;
	std::shared_ptr<GameState> game_state_;
	std::shared_ptr<RenderEngine::ShaderProgram> sprite_shader_program_;
};