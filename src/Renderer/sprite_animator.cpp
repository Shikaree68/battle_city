#include "sprite_animator.h"
#include "sprite.h"
namespace RenderEngine {
SpriteAnimator::SpriteAnimator(std::shared_ptr<Sprite> sprite)
	:sprite_(sprite)
	, current_frame_(0)
	, current_frame_duration_(sprite_->GetFrameDuration(0))
	, current_animation_time_(0)
	, total_duration_(0) {
	for(size_t frame_id = 0; frame_id < sprite_->GetFramesCount(); ++frame_id) {
		total_duration_ += sprite_->GetFrameDuration(frame_id);
	}
}

size_t SpriteAnimator::GetCurrentFrame() const {
	return current_frame_;
}

void SpriteAnimator::Update(const double delta) {
	current_animation_time_ += delta;
	while(current_animation_time_ >= current_frame_duration_) {
		current_animation_time_ -= current_frame_duration_;
		++current_frame_;
		if(current_frame_ == sprite_->GetFramesCount()) {
			current_frame_ = 0;
		}
		current_frame_duration_ = (sprite_->GetFrameDuration(0));
	}
}
double SpriteAnimator::GetTotalDuration() const {
	return total_duration_;
}
void SpriteAnimator::Reset() {
	current_frame_ = 0;
	current_frame_duration_ = sprite_->GetFrameDuration(0);
	current_animation_time_ = 0;
}
}
