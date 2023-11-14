#include "game_object_interface.h"

GameObject::GameObject(Type type, const glm::vec2& position, 
					   const glm::vec2& size, const float rotation, const float layer)
	: type_(type)
	, position_(position)
	, size_(size)
	, rotation_(rotation)
	, layer_(layer)
	, direction_(0, 1.f)
	, velocity_(0) {}

glm::vec2& GameObject::GetPosition() {
	return position_;
}

glm::vec2& GameObject::GetDirection() {
	return direction_;
}

double GameObject::GetVelocity() {
	return velocity_;
}

void GameObject::SetVelocity(const double velocity) {
	velocity_ = velocity;
}

bool GameObject::CheckCanCollide(const Type type) const {
	return true;
}

void GameObject::DoInCollide() {}

GameObject::Type GameObject::GetType() const {
	return type_;
}

const glm::vec2& GameObject::GetSize() const {
	return size_;
}

const std::vector<Physics::AABB>& GameObject::GetColliders() const {
	return colliders_;
}

GameObject::~GameObject() {}
