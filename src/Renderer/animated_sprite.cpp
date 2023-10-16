#include "animated_sprite.h"
#include "texture_2D.h"
#include <iostream>

namespace RenderEngine{


void AnimatedSprite::SetState(const std::string& new_state){
	auto state{states_.find(new_state)};
	if(state == states_.end()){
		std::cout << "Can't find animation state: " << new_state << std::endl;
	}

	if(state != current_animation_durations_){
		current_animation_time_ = 0;
		current_frame_ = 0;
		current_animation_durations_ = state;
		dirty_state_ = true;
	}
}

}
