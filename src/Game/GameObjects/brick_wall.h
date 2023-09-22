#pragma once

#include "game_object_interface.h"
#include <memory>

namespace RenderEngine{
class Sprite;
}
class BrickWall: public GameObject{
public:
	BrickWall(const std::shared_ptr<RenderEngine::Sprite> sprite,
			  const glm::vec2& position, const glm::vec2& size, const float rotation);
	void Render() const override;
	void Update(const uint64_t delta) override;
private:
	std::shared_ptr<RenderEngine::Sprite> sprite_;
};