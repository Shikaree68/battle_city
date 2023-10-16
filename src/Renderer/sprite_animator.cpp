#include "sprite_animator.h"
#include "sprite.h"
namespace RenderEngine{
SpriteAnimator::SpriteAnimator(std::shared_ptr<Sprite> sprite)
	:sprite_(sprite)
	, current_frame_(0)
	, current_frame_duration_(sprite_->GetFrameDuration(0))
	, current_animation_time_(0){}

void SpriteAnimator::Update(const uint32_t delta){
	current_animation_time_ += delta;

	while(current_animation_time_ >= current_frame_duration_){
		current_animation_time_ -= current_frame_duration_;
		++current_frame_;
		if(current_frame_ == sprite_->GetFramesCount()){
			current_frame_ = 0;
		}
		current_frame_duration_ = (sprite_->GetFrameDuration(0));
	}
}
}
