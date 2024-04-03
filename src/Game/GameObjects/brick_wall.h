#pragma once

#include "game_object_interface.h"

#include <array>
#include <memory>

namespace RenderEngine {
class Sprite;
}

class BrickWall : public GameObject {
public:
	enum class Type : uint8_t {
		All = 0,
		Top,
		Bottom,
		Left,
		Right,
		TopLeft,
		TopRight,
		BottomLeft,
		BottomRight
	};

	enum class State : uint8_t {
		All = 0,
		TopLeft,
		TopRight,
		Top,
		BottomLeft,
		Left,
		TopRight_BottomLeft,
		Top_BottomLeft,
		BottomRight,
		TopLeft_BottomRight,
		Right,
		Top_BottomRight,
		Bottom,
		TopLeft_Bottom,
		TopRight_Bottom,
		Destroyed
	};
	enum class Location : uint8_t {
		TopLeft = 0,
		TopRight,
		BottomLeft,
		BottomRight
	};
	BrickWall(const Type brick_wall_type,
			  const glm::vec2 &position,
			  const glm::vec2 &size,
			  const float rotation,
			  const float layer);
	void Render() const override;
	void Update(const double delta) override;
private:
	std::array<State, 4> state_;
	std::array<std::shared_ptr<RenderEngine::Sprite>, 15> sprites_;
	std::array<glm::vec2, 4> block_offsets_;
	std::array<Physics::Collider *, 4> location_to_collider_map_;
	void RenderBlock(const Location location) const;
	static State GetBrickStateAfterCollision(const State current_state, const Physics::CollisionDirection direction);
	static Physics::AABB GetAABBForBrickState(const Location location, const State state, const glm::vec2 &size);
	void CollisionCallback(const Location location, const GameObject &object, const Physics::CollisionDirection direction);
};