#pragma once

#include "game_object_interface.h"

#include <array>
#include <memory>

namespace RenderEngine{
class Sprite;
}

class Eagle: public GameObject{
public:
	enum class State : uint8_t {
		Alive = 0,
		Dead
	};
	Eagle(const glm::vec2& position,
		  const glm::vec2& size, 
		  const float rotation,
		  const float layer);
	void Render() const override;
	void Update(const uint64_t delta) override;
private:
 	std::array<std::shared_ptr<RenderEngine::Sprite>,2> sprites_;
	State state_;
};