#pragma once

#include "game_object_interface.h"

#include <array>
#include <memory>

namespace RenderEngine{
class Sprite;
}

class BetonWall: public GameObject{
public:
	enum class Type{
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

	enum class State{
        All = 0,
		Destroyed
	};
	enum class Location{
		TopLeft = 0,
		TopRight,
		BottomLeft,
		BottomRight
	};
	BetonWall(const Type brick_wall_type,
			  const glm::vec2& position,
			  const glm::vec2& size, 
			  const float rotation);
	void Render() const override;
	void Update(const uint64_t delta) override;
private:
	std::array<State, 4> current_state_;
 	std::shared_ptr<RenderEngine::Sprite> sprite_;
	std::array<glm::vec2, 4> block_offsets_;
	void RenderBlock(const Location location) const;
};