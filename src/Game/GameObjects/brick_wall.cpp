#include "brick_wall.h"

#include "../../Renderer/sprite.h"

BrickWall::BrickWall(const std::shared_ptr<RenderEngine::Sprite> sprite,
					 const glm::vec2& position,
					 const glm::vec2& size,
					 const float rotation)
	: GameObject(position, size, rotation)
	, sprite_(sprite){

}

void BrickWall::Render() const{
	sprite_->Render(position_,size_,rotation_);
}

void BrickWall::Update(const uint64_t delta){}
