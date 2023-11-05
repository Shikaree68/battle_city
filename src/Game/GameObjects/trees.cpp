#include "trees.h"

#include "../../Resources/resource_manager.h"
#include "../../Renderer/sprite.h"

using namespace std::literals;

Trees::Trees(const glm::vec2& position,
			 const glm::vec2& size,
			 const float rotation)
	: GameObject(position, size, rotation)
	, sprite_(ResourceManager::GetSprite("trees"s))
	, block_offsets_ {glm::vec2(0, size_.y / 2.f),
					  glm::vec2(size_.x / 2.f, size_.y / 2.f),
					  glm::vec2(0,0),
					  glm::vec2(size_.x / 2.f, 0)} {}


void Trees::RenderBlock(const Trees::Location location) const {
	sprite_->Render(position_ + block_offsets_[static_cast<size_t>(location)], size_ / 2.f, rotation_);
}

void Trees::Render() const {
	RenderBlock(Location::TopLeft);
	RenderBlock(Location::TopRight);
	RenderBlock(Location::BottomLeft);
	RenderBlock(Location::BottomRight);
}


void Trees::Update(const uint64_t delta) {}
