#pragma once

#include <memory>
#include <glm/vec2.hpp>

namespace Renderer{
class AnimatedSprite;
}

class Tank{
public:
	enum class Orientation{
		Top,
		Bottom,
		Left,
		Right,
	};
	Tank(std::shared_ptr<Renderer::AnimatedSprite> sprite, const float velocity, const glm::vec2& position);

	void Render() const;
	void SetOrientation(const Orientation orientation);
	void Move(bool is_move);
	void Update(const uint64_t delta);
private:
	Orientation orientation_;
	std::shared_ptr<Renderer::AnimatedSprite> sprite_;
	bool is_move_;
	float velocity_;
	glm::vec2 position_;
	glm::vec2 move_offset_;
};