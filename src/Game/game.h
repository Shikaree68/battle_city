#pragma once

#include <array>
#include <memory>
#include <glm/vec2.hpp>

class Tank;

class Game{
public:
	Game(const glm::ivec2& window_size);
	~Game();

	void Render();
	void Update(const uint64_t delta);
	void SetKey(const int key, int action);
	bool Initialize();

private:
	std::array<bool, 349> keys_;

	enum class GameState{
		Active,
		Pause,
	};

	GameState current_state_;
	glm::ivec2 window_size_;
	std::unique_ptr<Tank> tank_;
};