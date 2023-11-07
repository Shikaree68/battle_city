#pragma once

#include "game_object_interface.h"

#include <array>
#include <memory>

namespace RenderEngine{
class Sprite;
}

class Border: public GameObject{
public:

	Border(const glm::vec2& position,
		  const glm::vec2& size, 
		  const float rotation,
		  const float layer);
	void Render() const override;
	void Update(const double delta) override;
private:
 	std::shared_ptr<RenderEngine::Sprite> sprite_;
};