#pragma once

#include <vector>
#include <string>
#include <memory>

class GameObject;

class Level{
public:
	Level(const std::vector<std::string>& level_description);
	void Render() const;
	void Update(const uint32_t delta);
private:
	uint32_t width_;
	uint32_t height_;

	std::vector<std::shared_ptr<GameObject>> map_objects_;

};