#pragma once

#include <memory>
#include <glm/vec2.hpp>

#include "game_object_interface.h"

namespace RenderEngine{
class AnimatedSprite;
}

class Tank : public GameObject{
public:
	enum class Orientation{
		Top,
		Bottom,
		Left,
		Right,
	};
	Tank(std::shared_ptr<RenderEngine::AnimatedSprite> sprite, const float velocity, const glm::vec2& position, const glm::vec2& size);

	void Render() const override;
	void SetOrientation(const Orientation orientation);
	void Move(bool is_move);
	void Update(const uint64_t delta) override;
private:
	Orientation orientation_;
	std::shared_ptr<RenderEngine::AnimatedSprite> sprite_;
	bool is_move_;
	float velocity_;
	glm::vec2 move_offset_;
};