#pragma once

#include "game_state.h"

#include <vector>
#include <string>
#include <memory>

#include <glm/vec2.hpp>

class GameObject;
class Tank;

class Level : public GameState {
public:
	static constexpr uint32_t BLOCK_SIZE = 16;

	Level(const std::vector<std::string>& level_description);
	virtual void Render() const override;
	virtual void Update(const double delta) override;
	virtual void ProcessInput(const std::array<bool, 349>& keys) override; 
	virtual std::uint32_t GetStateWidth() const override;
	virtual std::uint32_t GetStateHeight() const override;

	const glm::ivec2& GetPlayerRespawn_1() const {
		return player_respawn_1_;
	};
	const glm::ivec2& GetPlayerRespawn_2() const {
		return player_respawn_2_;
	};
	const glm::ivec2& GetEnemyRespawn_1() const {
		return enemy_respawn_1_;
	};
	const glm::ivec2& GetEnemyRespawn_2() const {
		return enemy_respawn_2_;
	};
	const glm::ivec2& GetEnemyRespawn_3() const {
		return enemy_respawn_3_;
	};

	std::vector<std::shared_ptr<GameObject>> GetObjectsInArea(const glm::vec2 bottom_left, 
															  const glm::vec2 top_right) const;
	void InitPhysics();

private:
	uint32_t width_in_blocks_;
	uint32_t height_in_blocks_;
	uint64_t width_in_pixels_;
	uint64_t height_in_pixels_;


	glm::ivec2 player_respawn_1_;
	glm::ivec2 player_respawn_2_;
	glm::ivec2 enemy_respawn_1_;
	glm::ivec2 enemy_respawn_2_;
	glm::ivec2 enemy_respawn_3_;

	std::vector<std::shared_ptr<GameObject>> level_objects_;
	std::shared_ptr<Tank> tank_;
};