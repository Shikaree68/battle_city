#include "beton_wall.h"

#include "../../Resources/resource_manager.h"
#include "../../Renderer/sprite.h"

using namespace std::literals;

BetonWall::BetonWall(const Type beton_wall_type,
					 const glm::vec2& position,
					 const glm::vec2& size,
					 const float rotation,
					 const float layer)
	: GameObject(GameObject::Type::BetonWall, position, size, rotation, layer)
	, state_ {State::Destroyed,
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
		state_.fill(State::All);
		colliders_.emplace_back(glm::vec2(0), size_);
		break;
	case Type::Top:
		state_[static_cast<size_t>(Location::TopLeft)] = State::All;
		state_[static_cast<size_t>(Location::TopRight)] = State::All;
		colliders_.emplace_back(glm::vec2(0, size_.y / 2), size_);
		break;
	case Type::Bottom:
		state_[static_cast<size_t>(Location::BottomLeft)] = State::All;
		state_[static_cast<size_t>(Location::BottomRight)] = State::All;
		colliders_.emplace_back(glm::vec2(0), glm::vec2(size_.x, size_.y / 2));
		break;
	case Type::Left:
		state_[static_cast<size_t>(Location::TopLeft)] = State::All;
		state_[static_cast<size_t>(Location::BottomLeft)] = State::All;
		colliders_.emplace_back(glm::vec2(0), glm::vec2(size_.x / 2, size_.y));
		break;
	case Type::Right:
		state_[static_cast<size_t>(Location::TopRight)] = State::All;
		state_[static_cast<size_t>(Location::BottomRight)] = State::All;
		colliders_.emplace_back(glm::vec2(size_.x / 2, 0), size_);
		break;
	case Type::TopLeft:
		state_[static_cast<size_t>(Location::TopLeft)] = State::All;
		colliders_.emplace_back(glm::vec2(0, size_.y / 2), glm::vec2(size_.x / 2, size_.y));
		break;
	case Type::TopRight:
		state_[static_cast<size_t>(Location::TopRight)] = State::All;
		colliders_.emplace_back(glm::vec2(size_.x / 2, size_.y / 2), size_);
		break;
	case Type::BottomLeft:
		state_[static_cast<size_t>(Location::BottomLeft)] = State::All;
		colliders_.emplace_back(glm::vec2(0), glm::vec2(size_.x / 2, size_.y / 2));
		break;
	case Type::BottomRight:
		state_[static_cast<size_t>(Location::BottomRight)] = State::All;
		colliders_.emplace_back(glm::vec2(size_.x / 2, 0), glm::vec2(size_.x, size_.y / 2));
		break;
	}
}

void BetonWall::RenderBlock(const BetonWall::Location location) const {
	const State state = state_[static_cast<size_t>(location)];
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
