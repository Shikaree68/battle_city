#include "bullet.h"

#include "../../Resources/resource_manager.h"
#include "../../Renderer/sprite.h"

using namespace std::literals;
Bullet::Bullet(const double velocity,
			   const glm::vec2 &position,
			   const glm::vec2 &size,
			   const glm::vec2 &explosion_size,
			   const float layer)
	: GameObject(GameObject::Type::Bullet, position, size, 0.f, layer)
	, explosion_size_(explosion_size)
	, explosion_offset_((explosion_size_ - size_) / 2.f)
	, sprite_top_(ResourceManager::GetSprite("bullet_top"s))
	, sprite_bottom_(ResourceManager::GetSprite("bullet_bottom"s))
	, sprite_left_(ResourceManager::GetSprite("bullet_left"s))
	, sprite_right_(ResourceManager::GetSprite("bullet_right"s))
	, sprite_explosion_(ResourceManager::GetSprite("explosion"s))
	, animator_explosion_(sprite_explosion_)
	, orientation_(Orientation::Top)
	, max_velocity_(velocity)
	, is_active_(false)
	, is_explosion_(false) {

	auto collision_callback = [&](const GameObject &object, const Physics::CollisionDirection) {
		SetVelocity(0);
		is_explosion_ = true;
		explosion_timer_.Start(animator_explosion_.GetTotalDuration());
	};
	//SetVelocity(velocity);
	colliders_.emplace_back(glm::vec2(0), size_, collision_callback);
	explosion_timer_.SetCallback([&]() {
		is_explosion_ = false;
		is_active_ = false;
		animator_explosion_.Reset();
	});
}

void Bullet::Render() const {

	if (is_explosion_) {
		switch (orientation_) {
		case Bullet::Orientation::Top:
			sprite_explosion_->Render(position_ - explosion_offset_ + glm::vec2(0, size_.y / 2.f),
									  explosion_size_, rotation_, layer_ + 0.1f, animator_explosion_.GetCurrentFrame());
			break;
		case Bullet::Orientation::Bottom:
			sprite_explosion_->Render(position_ - explosion_offset_ - glm::vec2(0, size_.y / 2.f),
									  explosion_size_, rotation_, layer_ + 0.1f, animator_explosion_.GetCurrentFrame());
			break;
		case Bullet::Orientation::Left:
			sprite_explosion_->Render(position_ - explosion_offset_ - glm::vec2(size_.x / 2.f, 0),
									  explosion_size_, rotation_, layer_ + 0.1f, animator_explosion_.GetCurrentFrame());
			break;
		case Bullet::Orientation::Right:
			sprite_explosion_->Render(position_ - explosion_offset_ + glm::vec2(size_.x / 2.f, 0),
									  explosion_size_, rotation_, layer_ + 0.1f, animator_explosion_.GetCurrentFrame());
			break;
		}
	} else if (is_active_) {
		switch (orientation_) {
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

void Bullet::Update(const double delta) {
	if (is_explosion_) {
		animator_explosion_.Update(delta);
		explosion_timer_.Update(delta);
	}
}

void Bullet::Fire(const glm::vec2 &position, const glm::vec2 &direction) {
	position_ = position;
	direction_ = direction;

	if (direction_.x == 0.f) {
		orientation_ = (direction_.y < 0) ? Orientation::Bottom : Orientation::Top;
	} else {
		orientation_ = (direction_.x < 0) ? Orientation::Left : Orientation::Right;
	}
	is_active_ = true;
	SetVelocity(max_velocity_);
}
