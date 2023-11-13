#pragma once

#include<glm/vec2.hpp>
#include "../../Physics/physics_engine.h"

class GameObject {
public:
	GameObject(const glm::vec2& position, const glm::vec2& size, const float rotation, const float layer);

	virtual void Render() const = 0;
	virtual void Update(const double delta) = 0;
	virtual glm::vec2& GetPosition() {
		return position_;
	}
	virtual glm::vec2& GetDirection() {
		return direction_;
	}
	virtual double GetVelocity() {
		return velocity_;
	}
	virtual void SetVelocity(const double velocity);

	const glm::vec2& GetSize() const {
		return size_;
	}
	const std::vector<Physics::AABB>& GetColliders() const {
		return colliders_;
	}

	virtual ~GameObject();
protected:
	glm::vec2 position_;
	glm::vec2 size_;
	float rotation_;
	float layer_;

	glm::vec2 direction_;
	double velocity_;

	std::vector<Physics::AABB> colliders_;
};