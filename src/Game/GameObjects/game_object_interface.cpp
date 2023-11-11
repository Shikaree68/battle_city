#include "game_object_interface.h"

GameObject::GameObject(const glm::vec2& position, const glm::vec2& size, const float rotation, const float layer)
	: position_(position)
	, size_(size)
	, rotation_(rotation)
	, layer_(layer)
	, direction_(0, 1.f)
	, velocity_(0) {}

void GameObject::SetVelocity(const double velocity) {
	velocity_ = velocity;
}

GameObject::~GameObject() {}
