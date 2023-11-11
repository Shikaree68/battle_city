#pragma once

#include <memory>
#include <glm/vec2.hpp>

#include "game_object_interface.h"
#include "../../Renderer/sprite_animator.h"
#include "../../System/timer.h"

namespace RenderEngine{
class Sprite;
}

class Tank : public GameObject{
public:
	enum class Orientation : uint8_t {
		Top,
		Bottom,
		Left,
		Right,
	};
	Tank(const double max_velocity,
		 const glm::vec2& position, 
		 const glm::vec2& size,
		 const float layer);

	void Render() const override;
	void SetOrientation(const Orientation orientation);
	void Update(const double delta) override;
	double GetMaxVelocity() const {
		return max_velocity_;
	};
	void SetVelocity(const double velocity) override;
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

	std::shared_ptr<RenderEngine::Sprite> sprite_respawn_;
	RenderEngine::SpriteAnimator sprite_animator_respawn_;
	
	std::shared_ptr<RenderEngine::Sprite> sprite_shield_;
	RenderEngine::SpriteAnimator sprite_animator_shield_;

	double max_velocity_;
	bool is_spawning_;
	bool has_shield_;

	Timer timer_respawn_;
	Timer timer_shield_;
};