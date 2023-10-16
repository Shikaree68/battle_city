#include "tank.h"
#include "../../Renderer/sprite.h"


Tank::Tank(std::shared_ptr<RenderEngine::Sprite> sprite_top,
		   std::shared_ptr<RenderEngine::Sprite> sprite_bottom,
		   std::shared_ptr<RenderEngine::Sprite> sprite_left,
		   std::shared_ptr<RenderEngine::Sprite> sprite_right,
		   const float velocity,
		   const glm::vec2& position,
		   const glm::vec2& size)
	: GameObject(position, size, 0.f)
	, orientation_(Orientation::Top)
	, sprite_top_(sprite_top)
	, sprite_bottom_(sprite_bottom)
	, sprite_left_(sprite_left)
	, sprite_right_(sprite_right)
	, sprite_animator_top_(sprite_top_)
	, sprite_animator_bottom_(sprite_bottom_)
	, sprite_animator_left_(sprite_left_)
	, sprite_animator_right_(sprite_right_)
	, is_move_(false)
	, velocity_(velocity)
	, move_offset_(glm::vec2(0.f, 1.f)){}

void Tank::Render() const{
	switch(orientation_){
	case Tank::Orientation::Top:
		sprite_top_->Render(position_, size_, rotation_, sprite_animator_top_.GetCurrentFrame());
		break;
	case Tank::Orientation::Bottom:
		sprite_bottom_->Render(position_, size_, rotation_, sprite_animator_bottom_.GetCurrentFrame());
		break;
	case Tank::Orientation::Left:
		sprite_left_->Render(position_, size_, rotation_, sprite_animator_left_.GetCurrentFrame());
		break;
	case Tank::Orientation::Right:
		sprite_right_->Render(position_, size_, rotation_, sprite_animator_right_.GetCurrentFrame());
		break;
	}
}

void Tank::SetOrientation(const Orientation orientation){
	if(orientation_ == orientation){
		return;
	}

	orientation_ = orientation;
	switch(orientation_){
	case Tank::Orientation::Top:
		move_offset_.x = 0.f;
		move_offset_.y = 1.f;
		break;
	case Tank::Orientation::Bottom:
		move_offset_.x = 0.f;
		move_offset_.y = -1.f;
		break;
	case Tank::Orientation::Left:
		move_offset_.x = -1.f;
		move_offset_.y = 0.f;
		break;
	case Tank::Orientation::Right:
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

void Tank::Update(const uint32_t delta){
	if(is_move_){
		position_ += delta * velocity_ * move_offset_;
		switch(orientation_){
		case Tank::Orientation::Top:
			sprite_animator_top_.Update(delta);
			break;
		case Tank::Orientation::Bottom:
			sprite_animator_bottom_.Update(delta);
			break;
		case Tank::Orientation::Left:
			sprite_animator_left_.Update(delta);
			break;
		case Tank::Orientation::Right:
			sprite_animator_right_.Update(delta);
			break;
		}
	}
}


