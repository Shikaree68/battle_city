#include "water.h"

#include "../../Resources/resource_manager.h"
#include "../../Renderer/sprite.h"

using namespace std::literals;

Water::Water(const glm::vec2& position,
			 const glm::vec2& size,
			 const float rotation,
			 const float layer)
	: GameObject(position, size, rotation, layer)
	, sprite_(ResourceManager::GetSprite("water"s))
	, sprite_animator_(sprite_)
	, block_offsets_ {glm::vec2(0, size_.y / 2.f),
					  glm::vec2(size_.x / 2.f, size_.y / 2.f),
					  glm::vec2(0,0),
					  glm::vec2(size_.x / 2.f, 0)} {
	colliders_.emplace_back(glm::vec2(0), size_);
}


void Water::RenderBlock(const Water::Location location) const {
	sprite_->Render(position_ + block_offsets_[static_cast<size_t>(location)], size_ / 2.f, rotation_, layer_, sprite_animator_.GetCurrentFrame());
}

void Water::Render() const {
	RenderBlock(Location::TopLeft);
	RenderBlock(Location::TopRight);
	RenderBlock(Location::BottomLeft);
	RenderBlock(Location::BottomRight);
}


void Water::Update(const double delta) {
	sprite_animator_.Update(delta);
}
