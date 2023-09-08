#include "animated_sprite.h"
#include "texture_2D.h"
#include <iostream>

namespace Renderer{
AnimatedSprite::AnimatedSprite(std::shared_ptr<Texture2D> texture,
							   const std::string& initial_sub_texture,
							   std::shared_ptr<ShaderProgram> shader_program,
							   const glm::vec2& position,
							   const glm::vec2& size,
							   const float rotation)
	: Sprite(std::move(texture), initial_sub_texture,
			 std::move(shader_program), position, size, rotation){
	current_animation_durations_ = states_.end();
}
void AnimatedSprite::InsertState(const std::string& state, const std::vector<std::pair<std::string, uint64_t>>& sub_textures_duration){
	states_.emplace(state, sub_textures_duration);
}
void AnimatedSprite::Render() const{
	if(dirty_state_){
		auto& sub_texture{texture_->GetSubTexture(current_animation_durations_->second[current_frame_].first)};

		const GLfloat texture_coords[]{
			// U  V
			sub_texture.left_bottom_UV.x, sub_texture.left_bottom_UV.y,
			sub_texture.left_bottom_UV.x, sub_texture.right_top_UV.y,
			sub_texture.right_top_UV.x, sub_texture.right_top_UV.y,
			sub_texture.right_top_UV.x, sub_texture.left_bottom_UV.y,
		};
		texuter_coords_buffer_.Update(texture_coords, 2 * 4 * sizeof(GLfloat));
		dirty_state_ = false;
	}
	Sprite::Render();
}
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
void AnimatedSprite::Update(const uint64_t delta){
	if(current_animation_durations_ != states_.end()){
		current_animation_time_ += delta;

		while(current_animation_time_ >= current_animation_durations_->second[current_frame_].second){
			current_animation_time_ -= current_animation_durations_->second[current_frame_].second;
			++current_frame_;
			dirty_state_ = true;
			if(current_frame_ == current_animation_durations_->second.size()){
				current_frame_ = 0;
			}
		}
	}
}
}
