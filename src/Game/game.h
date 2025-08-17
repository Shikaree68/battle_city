#pragma once

#include <array>
#include <memory>
#include <glm/vec2.hpp>

class Tank;
class Level;
class StartScreen;

using dimension_t = std::uint32_t;

class Game {
public:
	Game(const glm::ivec2& window_size);
	~Game();

	void Render();
	void Update(double delta);
	void SetKey(int key, int action);
	bool Initialize();
	dimension_t GetCurrentWidth() const;
	dimension_t GetCurrentHeight() const;

private:
	enum class GameState{
		StartScreen,
		LevelStart,
		Level,
		Pause,
		Scores,
		GameOver
	};

	std::array<bool, 349> keys_;

	GameState state_;
	glm::ivec2 window_size_;
	std::shared_ptr<Tank> tank_;
	std::shared_ptr<Level> level_;
	std::shared_ptr<StartScreen> start_screen_;
};