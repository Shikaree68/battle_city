#pragma once

#include "game_object_interface.h"

#include <array>
#include <memory>

namespace  RenderEngine {
class Sprite;
}

class Bullet : public GameObject {
public:
	enum  class Orientation : uint8_t {
		Top,
		Bottom,
		Left,
		Right
	};

	Bullet(const double velocity, const glm::vec2& position, const glm::vec2& size, const float layer);
	void Render() const override;
	void Update(const double delta) override;
	bool IsActive() const {
		return is_active_;
	}
	void Fire(const glm::vec2& position, const glm::vec2& direction);
	void DoInCollide() override;

private:
	std::shared_ptr<RenderEngine::Sprite> sprite_top_;
	std::shared_ptr<RenderEngine::Sprite> sprite_bottom_;
	std::shared_ptr<RenderEngine::Sprite> sprite_left_;
	std::shared_ptr<RenderEngine::Sprite> sprite_right_;
	Orientation orientation_;
	double max_velocity_;
	bool is_active_;
};