#pragma once

#include <memory>
#include <glm/vec2.hpp>

#include "game_object_interface.h"
#include "../../Renderer/sprite_animator.h"

namespace RenderEngine{
class Sprite;
}

class Tank : public GameObject{
public:
	enum class Orientation{
		Top,
		Bottom,
		Left,
		Right,
	};
	Tank(const float velocity,
		 const glm::vec2& position, 
		 const glm::vec2& size);

	void Render() const override;
	void SetOrientation(const Orientation orientation);
	void Move(bool is_move);
	void Update(const uint64_t delta) override;
private:
	Orientation orientation_;

	std::shared_ptr<RenderEngine::Sprite> sprite_top_;
	std::shared_ptr<RenderEngine::Sprite> sprite_bottom_;
	std::shared_ptr<RenderEngine::Sprite> sprite_left_;
	std::shared_ptr<RenderEngine::Sprite> sprite_right_;
	RenderEngine::SpriteAnimator sprite_animator_top_;
	RenderEngine::SpriteAnimator sprite_animator_bottom_;
	RenderEngine::SpriteAnimator sprite_animator_left_;
	RenderEngine::SpriteAnimator sprite_animator_right_;

	bool is_move_;
	float velocity_;
	glm::vec2 move_offset_;
};