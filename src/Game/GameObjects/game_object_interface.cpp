#include "game_object_interface.h"

GameObject::GameObject(Type type, const glm::vec2 &position,
					   const glm::vec2 &size, const float rotation, const float layer)
	: type_(type)
	, position_(position)
	, size_(size)
	, rotation_(rotation)
	, layer_(layer)
	, direction_(0, 1.f)
	, velocity_(0) {}

glm::vec2 GameObject::GetPosition() const {
	return position_;
}

void GameObject::SetPosition(glm::vec2 new_position) {
	position_ = new_position;
}

glm::vec2 GameObject::GetDirection() const {
	return direction_;
}

double GameObject::GetVelocity() const {
	return velocity_;
}

void GameObject::SetVelocity(const double velocity) {
	velocity_ = velocity;
}

bool GameObject::CheckCanCollide(const Type type) const {
	return true;
}


GameObject::Type GameObject::GetType() const {
	return type_;
}

const glm::vec2 &GameObject::GetSize() const {
	return size_;
}

const std::vector<Physics::Collider> &GameObject::GetColliders() const {
	return colliders_;
}

GameObject::~GameObject() {}
