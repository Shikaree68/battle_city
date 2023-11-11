#pragma once

#include<glm/vec2.hpp>

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

	virtual ~GameObject();
protected:
	glm::vec2 position_;
	glm::vec2 size_;
	float rotation_;
	float layer_;

	glm::vec2 direction_;
	double velocity_;
};