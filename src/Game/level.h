#pragma once

#include <vector>
#include <string>
#include <memory>

class GameObject;

class Level{
public:
	Level(const std::vector<std::string>& level_description);
	void Render() const;
	void Update(const uint64_t delta);
private:
	uint64_t width_;
	uint64_t height_;

	std::vector<std::shared_ptr<GameObject>> map_objects_;

};