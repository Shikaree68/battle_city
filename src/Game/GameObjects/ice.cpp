#include "ice.h"

#include "../../Resources/resource_manager.h"
#include "../../Renderer/sprite.h"

using namespace std::literals;

Ice::Ice(const glm::vec2& position,
		 const glm::vec2& size,
		 const float rotation,
		 const float layer)
	: GameObject(GameObject::Type::Ice ,position, size, rotation, layer)
	, sprite_(ResourceManager::GetSprite("ice"s))
	, block_offsets_ {glm::vec2(0, size_.y / 2.f),
					  glm::vec2(size_.x / 2.f, size_.y / 2.f),
					  glm::vec2(0,0),
					  glm::vec2(size_.x / 2.f, 0)} {}


void Ice::RenderBlock(const Ice::Location location) const {
	sprite_->Render(position_ + block_offsets_[static_cast<size_t>(location)], size_ / 2.f, rotation_, layer_);
}

void Ice::Render() const {
	RenderBlock(Location::TopLeft);
	RenderBlock(Location::TopRight);
	RenderBlock(Location::BottomLeft);
	RenderBlock(Location::BottomRight);
}


void Ice::Update(const double delta) {}
