#include "eagle.h"

#include "../../Resources/resource_manager.h"
#include "../../Renderer/sprite.h"

using namespace std::literals;

Eagle::Eagle(const glm::vec2& position,
			 const glm::vec2& size,
			 const float rotation)
	: GameObject(position, size, rotation)
	, sprites_ {ResourceManager::GetSprite("eagle_alive"s),
	ResourceManager::GetSprite("eagle_dead"s)}
	, state_(State::Alive) {}

void Eagle::Render() const {
	sprites_[static_cast<size_t>(state_)]->Render(position_, size_, rotation_);
}

void Eagle::Update(const uint64_t delta) {}
