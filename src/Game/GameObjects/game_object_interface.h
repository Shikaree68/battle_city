#pragma once

#include<glm/vec2.hpp>

class GameObject{
public:
	GameObject(const glm::vec2& position, const glm::vec2& size, const float rotation);
	virtual ~GameObject();

	virtual void Render() const = 0;
	virtual void Update(const uint64_t delta) = 0;

protected:
	glm::vec2 position_;
	glm::vec2 size_;
	float rotation_;
};