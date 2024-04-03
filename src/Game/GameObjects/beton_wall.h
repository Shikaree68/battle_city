#pragma once

#include "game_object_interface.h"

#include <array>
#include <memory>

namespace RenderEngine{
class Sprite;
}

class BetonWall: public GameObject{
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
		Destroyed
	};
	enum class Location : uint8_t {
		TopLeft = 0,
		TopRight,
		BottomLeft,
		BottomRight
	};
	BetonWall(const Type beton_wall_type,
			  const glm::vec2& position,
			  const glm::vec2& size, 
			  const float rotation,
			  const float layer);
	void Render() const override;
	void Update(const double delta) override;
private:
	std::array<State, 4> state_;
 	std::shared_ptr<RenderEngine::Sprite> sprite_;
	std::array<glm::vec2, 4> block_offsets_;
	void RenderBlock(const Location location) const;
};