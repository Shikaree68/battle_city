#pragma once

#include<glm/vec2.hpp>
#include "../../Physics/physics_engine.h"

class GameObject {
public:
	enum class Type {
		BetonWall,
		Border,
		BrickWall,
		Bullet,
		Eagle,
		Ice,
		Tank,
		Trees,
		Water,
		Unknown
	};
	GameObject(const Type type, const glm::vec2& position,
			   const glm::vec2& size, const float rotation, const float layer);
	virtual void Render() const = 0;
	virtual void Update(const double delta) = 0;
	virtual glm::vec2 GetPosition() const;
	virtual void SetPosition(glm::vec2 new_position);
	virtual glm::vec2 GetDirection() const;
	virtual double GetVelocity() const;
	virtual void SetVelocity(const double velocity);
	virtual bool CheckCanCollide(const Type type) const;

	Type GetType() const;
	const glm::vec2& GetSize() const;
	const std::vector<Physics::Collider>& GetColliders() const;

	virtual ~GameObject();
protected:
	glm::vec2 position_;
	const glm::vec2 size_;
	float rotation_;
	float layer_;
	Type type_;

	glm::vec2 direction_;
	double velocity_;
	std::vector<Physics::Collider> colliders_;
};