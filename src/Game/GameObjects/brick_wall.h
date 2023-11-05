#pragma once

#include "game_object_interface.h"

#include <array>
#include <memory>

namespace RenderEngine{
class Sprite;
}

class BrickWall: public GameObject{
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
        Top_left,
        Top_right,
        Top,
        Bottom_left,
        Left,
        Top_right_bottom_left,
        Top_bottom_left,
        Bottom_right,
        Top_left_bottom_right,
        Right,
        Top_bottom_right,
        Bottom,
        Top_left_bottom,
        Top_right_bottom,
		Destroyed
	};
	enum class Location : uint8_t {
		TopLeft = 0,
		TopRight,
		BottomLeft,
		BottomRight
	};
	BrickWall(const Type brick_wall_type,
			  const glm::vec2& position,
			  const glm::vec2& size, 
			  const float rotation);
	void Render() const override;
	void Update(const uint64_t delta) override;
private:
	std::array<State, 4> current_state_;
 	std::array<std::shared_ptr<RenderEngine::Sprite>, 15> sprites_;
	std::array<glm::vec2, 4> block_offsets_;
	void RenderBlock(const Location location) const;
};