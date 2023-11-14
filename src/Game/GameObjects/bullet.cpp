#include "bullet.h"

#include "../../Resources/resource_manager.h"
#include "../../Renderer/sprite.h"

using namespace std::literals;
Bullet::Bullet(const double velocity, const glm::vec2& position, const glm::vec2& size, const float layer)
	: GameObject(GameObject::Type::Bullet, position, size, 0.f, layer)
	, sprite_top_(ResourceManager::GetSprite("bullet_top"s))
	, sprite_bottom_(ResourceManager::GetSprite("bullet_bottom"s))
	, sprite_left_(ResourceManager::GetSprite("bullet_left"s))
	, sprite_right_(ResourceManager::GetSprite("bullet_right"s))
	, orientation_(Orientation::Top)
	, max_velocity_(velocity)
	, is_active_(false) {
	SetVelocity(velocity);
	colliders_.emplace_back(glm::vec2(0), size_);
}

void Bullet::Render() const {
	if(is_active_) {
		switch(orientation_) {
		case Bullet::Orientation::Top:
			sprite_top_->Render(position_, size_, rotation_, layer_);
			break;
		case Bullet::Orientation::Bottom:
			sprite_bottom_->Render(position_, size_, rotation_, layer_);
			break;
		case Bullet::Orientation::Left:
			sprite_left_->Render(position_, size_, rotation_, layer_);
			break;
		case Bullet::Orientation::Right:
			sprite_right_->Render(position_, size_, rotation_, layer_);
			break;
		}
	}
}

void Bullet::Update(const double delta) {}

void Bullet::Fire(const glm::vec2& position, const glm::vec2& direction) {
	position_ = position;
	direction_ = direction;

	if(direction_.x == 0.f) {
		orientation_ = (direction_.y < 0) ? Orientation::Bottom : Orientation::Top;
	} else {
		orientation_ = (direction_.x < 0) ? Orientation::Left : Orientation::Right;
	}
	is_active_ = true;
	SetVelocity(max_velocity_);
}

void Bullet::DoInCollide() {
	SetVelocity(0);
	is_active_ = false;
}
