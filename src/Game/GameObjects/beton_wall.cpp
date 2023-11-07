#include "beton_wall.h"

#include "../../Resources/resource_manager.h"
#include "../../Renderer/sprite.h"

using namespace std::literals;

BetonWall::BetonWall(const Type beton_wall_type,
					 const glm::vec2& position,
					 const glm::vec2& size,
					 const float rotation,
					 const float layer)
	: GameObject(position, size, rotation, layer)
	, current_state_ {State::Destroyed,
					  State::Destroyed,
					  State::Destroyed,
					  State::Destroyed}
	, sprite_(ResourceManager::GetSprite("beton_wall"s))
	, block_offsets_ {glm::vec2(0, size_.y / 2.f),
					  glm::vec2(size_.x / 2.f, size_.y / 2.f),
					  glm::vec2(0,0),
					  glm::vec2(size_.x / 2.f, 0)} {
	switch(beton_wall_type) {
	case Type::All:
		current_state_.fill(State::All);
		break;
	case Type::Top:
		current_state_[static_cast<size_t>(Location::TopLeft)] = State::All;
		current_state_[static_cast<size_t>(Location::TopRight)] = State::All;
		break;
	case Type::Bottom:
		current_state_[static_cast<size_t>(Location::BottomLeft)] = State::All;
		current_state_[static_cast<size_t>(Location::BottomRight)] = State::All;
		break;
	case Type::Left:
		current_state_[static_cast<size_t>(Location::TopLeft)] = State::All;
		current_state_[static_cast<size_t>(Location::BottomLeft)] = State::All;
		break;
	case Type::Right:
		current_state_[static_cast<size_t>(Location::TopRight)] = State::All;
		current_state_[static_cast<size_t>(Location::BottomRight)] = State::All;
		break;
	case Type::TopLeft:
		current_state_[static_cast<size_t>(Location::TopLeft)] = State::All;
		break;
	case Type::TopRight:
		current_state_[static_cast<size_t>(Location::TopRight)] = State::All;
		break;
	case Type::BottomLeft:
		current_state_[static_cast<size_t>(Location::BottomLeft)] = State::All;
		break;
	case Type::BottomRight:
		current_state_[static_cast<size_t>(Location::BottomRight)] = State::All;
		break;
	}
}

void BetonWall::RenderBlock(const BetonWall::Location location) const {
	const State state = current_state_[static_cast<size_t>(location)];
	if(state != State::Destroyed) {
		sprite_->Render(position_ + block_offsets_[static_cast<size_t>(location)], size_ / 2.f, rotation_, layer_);
	}
}

void BetonWall::Render() const {
	RenderBlock(Location::TopLeft);
	RenderBlock(Location::TopRight);
	RenderBlock(Location::BottomLeft);
	RenderBlock(Location::BottomRight);
}


void BetonWall::Update(const double delta) {}
