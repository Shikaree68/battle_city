#pragma once
#include <unordered_set>
#include <memory>

#include <glm/vec2.hpp>

class GameObject;
class Level;

namespace Physics {

//Axes Aligned Bounding Box
struct AABB {
	AABB(const glm::vec2& a_bottom_left, const glm::vec2& a_top_right)
		: bottom_left(a_bottom_left)
		, top_right(a_top_right){}
	glm::vec2 bottom_left;
	glm::vec2 top_right;
};

class PhysicsEngine {
public:
	~PhysicsEngine() = delete;
	PhysicsEngine() = delete;
	PhysicsEngine(const PhysicsEngine&) = delete;
	PhysicsEngine& operator=(const PhysicsEngine&) = delete;
	PhysicsEngine& operator=(PhysicsEngine&&) = delete;
	PhysicsEngine(PhysicsEngine&&) = delete;

	static void Initialize();
	static void Terminate();

	static void Update(const double delta);
	static void AddDynamicGameObject(std::shared_ptr<GameObject> game_object);
	static void SetCurrentLevel(std::shared_ptr<Level> level);

private:
	static std::unordered_set<std::shared_ptr<GameObject>> dynamic_objects_;
	static std::shared_ptr<Level> level_;
	static bool CheckIntersection(const std::vector<AABB>& colliders1, const glm::vec2& position1,
								 const std::vector<AABB>& colliders2, const glm::vec2& position2);
};
}