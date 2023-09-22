#pragma once

#include "sprite.h"

#include <map>
#include <string>
#include <vector>

namespace RenderEngine{

class AnimatedSprite: public Sprite{
public:
	AnimatedSprite(std::shared_ptr<Texture2D> texture,
				   const std::string& initial_sub_texture,
				   std::shared_ptr<ShaderProgram> shader_program);

	void InsertState(const std::string& state,
					 const std::vector<std::pair<std::string, uint64_t>>& sub_textures_duration);

	void Render(const glm::vec2& position, const glm::vec2& size, const float rotation) const override;
	void SetState(const std::string& new_state);
	void Update(const uint64_t delta);

private:
	std::map<std::string, std::vector<std::pair<std::string, uint64_t>>> states_;
	size_t current_frame_{};
	uint64_t current_animation_time_{};
	std::map<std::string, std::vector<std::pair<std::string, uint64_t>>>::const_iterator current_animation_durations_;
	mutable bool dirty_state_{false};
};
}  // namespace Renderer