#pragma once

#include<glm/vec2.hpp>

class GameObject{
public:
	GameObject(const glm::vec2& position, const glm::vec2& size, const float rotation, const float layer);
	virtual ~GameObject();

	virtual void Render() const = 0;
	virtual void Update(const double delta) = 0;

protected:
	glm::vec2 position_;
	glm::vec2 size_;
	float rotation_;
	float layer_;
};