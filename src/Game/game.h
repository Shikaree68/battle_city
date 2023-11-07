#pragma once

#include <array>
#include <memory>
#include <glm/vec2.hpp>
#include "level.h"

class Tank;

class Game{
public:
	Game(const glm::ivec2& window_size);
	~Game();

	void Render();
	void Update(const double delta);
	void SetKey(const int key, int action);
	bool Initialize();
	size_t GetCurrentLevelWidth() const;
	size_t GetCurrentLevelHeight() const;

private:
	std::array<bool, 349> keys_;

	enum class GameState{
		Active,
		Pause,
	};

	GameState current_state_;
	glm::ivec2 window_size_;
	std::unique_ptr<Tank> tank_;
	std::unique_ptr<Level> level_;
};