#pragma once

#include <vector>
#include <string>
#include <memory>

#include <glm/vec2.hpp>

class GameObject;

class Level{
public:
	static constexpr uint32_t BLOCK_SIZE = 16;

	Level(const std::vector<std::string>& level_description);
	void Render() const;
	void Update(const double delta);
	uint64_t GetLevelWidth() const;
	uint64_t GetLevelHeight() const;

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


};