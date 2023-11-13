#include "border.h"

#include "../../Resources/resource_manager.h"
#include "../../Renderer/sprite.h"

using namespace std::literals;

Border::Border(const glm::vec2& position,
			   const glm::vec2& size,
			   const float rotation,
			   const float layer)
	: GameObject(position, size, rotation, layer)
	, sprite_(ResourceManager::GetSprite("border"s)) {
	colliders_.emplace_back(glm::vec2(0), size_);
}

void Border::Render() const {
	sprite_->Render(position_, size_, rotation_, layer_);
}

void Border::Update(const double delta) {}
