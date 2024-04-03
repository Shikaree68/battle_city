#include "brick_wall.h"

#include "../../Resources/resource_manager.h"
#include "../../Renderer/sprite.h"

using namespace std::literals;

BrickWall::BrickWall(const Type brick_wall_type,
					 const glm::vec2 &position,
					 const glm::vec2 &size,
					 const float rotation,
					 const float layer)
	: GameObject(GameObject::Type::BrickWall, position, size, rotation, layer)
	, state_ { State::Destroyed,
			   State::Destroyed,
			   State::Destroyed,
			   State::Destroyed }
	, block_offsets_ { glm::vec2(0, size_.y / 2.f),
					   glm::vec2(size_.x / 2.f, size_.y / 2.f),
					   glm::vec2(0,0),
					   glm::vec2(size_.x / 2.f, 0) } {
	sprites_[static_cast<size_t>(State::All)] = ResourceManager::GetSprite("brick_all"s);
	sprites_[static_cast<size_t>(State::TopLeft)] = ResourceManager::GetSprite("brick_top_left"s);
	sprites_[static_cast<size_t>(State::TopRight)] = ResourceManager::GetSprite("brick_top_right"s);
	sprites_[static_cast<size_t>(State::Top)] = ResourceManager::GetSprite("brick_top"s);
	sprites_[static_cast<size_t>(State::BottomLeft)] = ResourceManager::GetSprite("brick_bottom_left"s);
	sprites_[static_cast<size_t>(State::Left)] = ResourceManager::GetSprite("brick_left"s);
	sprites_[static_cast<size_t>(State::TopRight_BottomLeft)] = ResourceManager::GetSprite("brick_top_right_bottom_left"s);
	sprites_[static_cast<size_t>(State::Top_BottomLeft)] = ResourceManager::GetSprite("brick_top_bottom_left"s);
	sprites_[static_cast<size_t>(State::BottomRight)] = ResourceManager::GetSprite("brick_bottom_right"s);
	sprites_[static_cast<size_t>(State::TopLeft_BottomRight)] = ResourceManager::GetSprite("brick_top_left_bottom_right"s);
	sprites_[static_cast<size_t>(State::Right)] = ResourceManager::GetSprite("brick_right"s);
	sprites_[static_cast<size_t>(State::Top_BottomRight)] = ResourceManager::GetSprite("brick_top_bottom_right"s);
	sprites_[static_cast<size_t>(State::Bottom)] = ResourceManager::GetSprite("brick_bottom"s);
	sprites_[static_cast<size_t>(State::TopLeft_Bottom)] = ResourceManager::GetSprite("brick_top_left_bottom"s);
	sprites_[static_cast<size_t>(State::TopRight_Bottom)] = ResourceManager::GetSprite("brick_top_right_bottom"s);

	auto CollisionCallbackTopLeft = [&](const GameObject &object, const Physics::CollisionDirection direction) {
		CollisionCallback(Location::TopLeft, object, direction);
	};
	auto CollisionCallbackTopRight = [&](const GameObject &object, const Physics::CollisionDirection direction) {
		CollisionCallback(Location::TopRight, object, direction);
	};
	auto CollisionCallbackBottomLeft = [&](const GameObject &object, const Physics::CollisionDirection direction) {
		CollisionCallback(Location::BottomLeft, object, direction);
	};
	auto CollisionCallbackBottomRight = [&](const GameObject &object, const Physics::CollisionDirection direction) {
		CollisionCallback(Location::BottomRight, object, direction);
	};

	location_to_collider_map_.fill(nullptr);
	colliders_.reserve(4);

	switch (brick_wall_type) {
	case Type::All:
		state_.fill(State::All);
		location_to_collider_map_[static_cast<size_t>(Location::TopLeft)] =
			&(colliders_.emplace_back(GetAABBForBrickState(Location::TopLeft, State::All, size_), CollisionCallbackTopLeft));
		location_to_collider_map_[static_cast<size_t>(Location::TopRight)] =
			&(colliders_.emplace_back(GetAABBForBrickState(Location::TopRight, State::All, size_), CollisionCallbackTopRight));
		location_to_collider_map_[static_cast<size_t>(Location::BottomLeft)] =
			&(colliders_.emplace_back(GetAABBForBrickState(Location::BottomLeft, State::All, size_), CollisionCallbackBottomLeft));
		location_to_collider_map_[static_cast<size_t>(Location::BottomRight)] =
			&(colliders_.emplace_back(GetAABBForBrickState(Location::BottomRight, State::All, size_), CollisionCallbackBottomRight));
		break;
	case Type::Top:
		state_[static_cast<size_t>(Location::TopLeft)] = State::All;
		state_[static_cast<size_t>(Location::TopRight)] = State::All;
		location_to_collider_map_[static_cast<size_t>(Location::TopLeft)] =
			&(colliders_.emplace_back(GetAABBForBrickState(Location::TopLeft, State::All, size_), CollisionCallbackTopLeft));
		location_to_collider_map_[static_cast<size_t>(Location::TopRight)] =
			&(colliders_.emplace_back(GetAABBForBrickState(Location::TopRight, State::All, size_), CollisionCallbackTopRight));
		break;
	case Type::Bottom:
		state_[static_cast<size_t>(Location::BottomLeft)] = State::All;
		state_[static_cast<size_t>(Location::BottomRight)] = State::All;
		location_to_collider_map_[static_cast<size_t>(Location::BottomLeft)] =
			&(colliders_.emplace_back(GetAABBForBrickState(Location::BottomLeft, State::All, size_), CollisionCallbackBottomLeft));
		location_to_collider_map_[static_cast<size_t>(Location::BottomRight)] =
			&(colliders_.emplace_back(GetAABBForBrickState(Location::BottomRight, State::All, size_), CollisionCallbackBottomRight));
		break;
	case Type::Left:
		state_[static_cast<size_t>(Location::TopLeft)] = State::All;
		state_[static_cast<size_t>(Location::BottomLeft)] = State::All;
		location_to_collider_map_[static_cast<size_t>(Location::TopLeft)] =
			&(colliders_.emplace_back(GetAABBForBrickState(Location::TopLeft, State::All, size_), CollisionCallbackTopLeft));
		location_to_collider_map_[static_cast<size_t>(Location::BottomLeft)] =
			&(colliders_.emplace_back(GetAABBForBrickState(Location::BottomLeft, State::All, size_), CollisionCallbackBottomLeft));
		break;
	case Type::Right:
		state_[static_cast<size_t>(Location::TopRight)] = State::All;
		state_[static_cast<size_t>(Location::BottomRight)] = State::All;
		location_to_collider_map_[static_cast<size_t>(Location::TopRight)] =
			&(colliders_.emplace_back(GetAABBForBrickState(Location::TopRight, State::All, size_), CollisionCallbackTopRight));
		location_to_collider_map_[static_cast<size_t>(Location::BottomRight)] =
			&(colliders_.emplace_back(GetAABBForBrickState(Location::BottomRight, State::All, size_), CollisionCallbackBottomRight));
		break;
	case Type::TopLeft:
		state_[static_cast<size_t>(Location::TopLeft)] = State::All;
		location_to_collider_map_[static_cast<size_t>(Location::TopLeft)] =
			&(colliders_.emplace_back(GetAABBForBrickState(Location::TopLeft, State::All, size_), CollisionCallbackTopLeft));
		break;
	case Type::TopRight:
		state_[static_cast<size_t>(Location::TopRight)] = State::All;
		location_to_collider_map_[static_cast<size_t>(Location::TopRight)] =
			&(colliders_.emplace_back(GetAABBForBrickState(Location::TopRight, State::All, size_), CollisionCallbackTopRight));
		break;
	case Type::BottomLeft:
		state_[static_cast<size_t>(Location::BottomLeft)] = State::All;
		location_to_collider_map_[static_cast<size_t>(Location::BottomLeft)] =
			&(colliders_.emplace_back(GetAABBForBrickState(Location::BottomLeft, State::All, size_), CollisionCallbackBottomLeft));
		break;
	case Type::BottomRight:
		state_[static_cast<size_t>(Location::BottomRight)] = State::All;
		location_to_collider_map_[static_cast<size_t>(Location::BottomRight)] =
			&(colliders_.emplace_back(GetAABBForBrickState(Location::BottomRight, State::All, size_), CollisionCallbackBottomRight));
		break;
	}
}

void BrickWall::RenderBlock(const BrickWall::Location location) const {
	const State state = state_[static_cast<size_t>(location)];
	if (state != State::Destroyed) {
		sprites_[static_cast<size_t>(state)]->Render(position_ + block_offsets_[static_cast<size_t>(location)], size_ / 2.f, rotation_, layer_);
	}
}

BrickWall::State BrickWall::GetBrickStateAfterCollision(const State current_state, const Physics::CollisionDirection direction) {
	switch (current_state) {
	case State::All:
		switch (direction) {
		case Physics::CollisionDirection::Left:
			return State::Right;
		case Physics::CollisionDirection::Right:
			return State::Left;
		case Physics::CollisionDirection::Top:
			return State::Top;
		case Physics::CollisionDirection::Bottom:
			return State::Bottom;
		}

	case State::Top:
		switch (direction) {
		case Physics::CollisionDirection::Left:
			return State::TopRight;
		case Physics::CollisionDirection::Right:
			return State::TopLeft;
		case Physics::CollisionDirection::Top:
			return State::Destroyed;
		case Physics::CollisionDirection::Bottom:
			return State::Destroyed;
		}

	case State::Bottom:
		switch (direction) {
		case Physics::CollisionDirection::Left:
			return State::BottomRight;
		case Physics::CollisionDirection::Right:
			return State::BottomLeft;
		case Physics::CollisionDirection::Top:
			return State::Destroyed;
		case Physics::CollisionDirection::Bottom:
			return State::Destroyed;
		}

	case State::Left:
		switch (direction) {
		case Physics::CollisionDirection::Left:
			return State::Destroyed;
		case Physics::CollisionDirection::Right:
			return State::Destroyed;
		case Physics::CollisionDirection::Top:
			return State::TopLeft;
		case Physics::CollisionDirection::Bottom:
			return State::BottomLeft;
		}

	case State::Right:
		switch (direction) {
		case Physics::CollisionDirection::Left:
			return State::Destroyed;
		case Physics::CollisionDirection::Right:
			return State::Destroyed;
		case Physics::CollisionDirection::Top:
			return State::TopRight;
		case Physics::CollisionDirection::Bottom:
			return State::BottomRight;
		}

	default:
		return State::Destroyed;
	}
}

Physics::AABB BrickWall::GetAABBForBrickState(const Location location, const State state, const glm::vec2 &size) {
	glm::vec2 block_offset(0);
	switch (location) {
	case Location::BottomLeft:
		break;
	case Location::BottomRight:
		block_offset.x += size.x / 2;
		break;
	case Location::TopLeft:
		block_offset.y += size.y / 2;
		break;
	case Location::TopRight:
		block_offset += size / 2.f;
		break;
	}

	glm::vec2 bottom_left(0);
	glm::vec2 top_right(0);

	switch (state) {
	case BrickWall::State::All:
		top_right = glm::vec2(size.x / 2, size.y / 2);
		break;
	case BrickWall::State::TopLeft:
		bottom_left = glm::vec2(0, size.y / 4);
		top_right = glm::vec2(size.x / 4, size.y / 2);
		break;
	case BrickWall::State::TopRight:
		bottom_left = glm::vec2(size.x / 4, size.y / 4);
		top_right = glm::vec2(size.x / 2, size.y / 2);
		break;
	case BrickWall::State::Top:
		bottom_left = glm::vec2(0, size.y / 4);
		top_right = glm::vec2(size.x / 2, size.y / 2);
		break;
	case BrickWall::State::BottomLeft:
		top_right = glm::vec2(size.x / 4, size.y / 4);
		break;
	case BrickWall::State::Left:
		top_right = glm::vec2(size.x / 4, size.y / 2);
		break;
	case BrickWall::State::TopRight_BottomLeft:
		top_right = glm::vec2(size.x / 2, size.y / 2);
		break;
	case BrickWall::State::Top_BottomLeft:
		top_right = glm::vec2(size.x / 2, size.y / 2);
		break;
	case BrickWall::State::BottomRight:
		bottom_left = glm::vec2(size.x / 4, 0);
		top_right = glm::vec2(size.x / 2, size.y / 4);
		break;
	case BrickWall::State::TopLeft_BottomRight:
		top_right = glm::vec2(size.x / 2, size.y / 2);
		break;
	case BrickWall::State::Right:
		bottom_left = glm::vec2(size.x / 4, 0);
		top_right = glm::vec2(size.x / 2, size.y / 2);
		break;
	case BrickWall::State::Top_BottomRight:
		top_right = glm::vec2(size.x / 2, size.y / 2);
		break;
	case BrickWall::State::Bottom:
		top_right = glm::vec2(size.x / 2, size.y / 4);
		break;
	case BrickWall::State::TopLeft_Bottom:
		top_right = glm::vec2(size.x / 2, size.y / 2);
		break;
	case BrickWall::State::TopRight_Bottom:
		top_right = glm::vec2(size.x / 2, size.y / 2);
		break;
	case BrickWall::State::Destroyed:
		break;
	}
	return { bottom_left + block_offset, top_right + block_offset };
}

void BrickWall::CollisionCallback(const Location location, const GameObject &object, const Physics::CollisionDirection direction) {
	if (object.GetType() != GameObject::Type::Bullet) {
		return;
	}
	state_[static_cast<size_t>(location)] = GetBrickStateAfterCollision(state_[static_cast<size_t>(location)], direction);

	if (state_[static_cast<size_t>(location)] != State::Destroyed) {
		location_to_collider_map_[static_cast<size_t>(location)]->bounding_box = GetAABBForBrickState(location, state_[static_cast<size_t>(location)], size_);
	} else {
		location_to_collider_map_[static_cast<size_t>(location)]->is_active = false;
	}
}

void BrickWall::Render() const {
	RenderBlock(Location::TopLeft);
	RenderBlock(Location::TopRight);
	RenderBlock(Location::BottomLeft);
	RenderBlock(Location::BottomRight);
}


void BrickWall::Update(const double delta) {}
