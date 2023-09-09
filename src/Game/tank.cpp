#include "tank.h"
#include "../Renderer/animated_sprite.h"


Tank::Tank(std::shared_ptr<RenderEngine::AnimatedSprite> sprite, const float velocity, const glm::vec2& position)
	: orientation_(Orientation::Top)
	, sprite_(sprite)
	, is_move_(false)
	, velocity_(velocity)
	, position_(position)
	, move_offset_(glm::vec2(0.f, 1.f)){
	sprite_->SetPosition(position_);
}

void Tank::Render() const{
	sprite_->Render();;
}

void Tank::SetOrientation(const Orientation orientation){
	if(orientation_ == orientation){
		return;
	}

	orientation_ = orientation;
	switch(orientation_){
	case Tank::Orientation::Top:
		sprite_->SetState("tank_top_state");
		move_offset_.x = 0.f;
		move_offset_.y = 1.f;
		break;
	case Tank::Orientation::Bottom:
		sprite_->SetState("tank_bottom_state");
		move_offset_.x = 0.f;
		move_offset_.y = -1.f;
		break;
	case Tank::Orientation::Left:
		sprite_->SetState("tank_left_state");
		move_offset_.x = -1.f;
		move_offset_.y = 0.f;
		break;
	case Tank::Orientation::Right:
		sprite_->SetState("tank_right_state");
		move_offset_.x = 1.f;
		move_offset_.y = 0.f;
		break;
	default:
		break;
	}
}

void Tank::Move(bool is_move){
	is_move_ = is_move;
}

void Tank::Update(const uint64_t delta){
	if(is_move_){
		position_ += delta * velocity_ * move_offset_;
		sprite_->SetPosition(position_);
		sprite_->Update(delta);
	}
}


