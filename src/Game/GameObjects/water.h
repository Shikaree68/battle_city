#pragma once

#include "game_object_interface.h"
#include "../../Renderer/sprite_animator.h"
#include <array>
#include <memory>

namespace RenderEngine{
class Sprite;
}

class Water: public GameObject{
public:

	enum class Location : uint8_t {
		TopLeft = 0,
		TopRight,
		BottomLeft,
		BottomRight
	};
	Water(const glm::vec2& position,
		  const glm::vec2& size, 
		  const float rotation,
		  const float layer);
	void Render() const override;
	void Update(const double delta) override;
private:
 	std::shared_ptr<RenderEngine::Sprite> sprite_;
	std::array<glm::vec2, 4> block_offsets_;
	RenderEngine::SpriteAnimator sprite_animator_;
	void RenderBlock(const Location location) const;
};