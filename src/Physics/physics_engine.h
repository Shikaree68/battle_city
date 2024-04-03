#pragma once

#include <unordered_set>
#include <memory>
#include <functional>

#include <glm/vec2.hpp>

class GameObject;
class Level;

namespace Physics {
enum class CollisionDirection : uint8_t {
	Top,
	Bottom,
	Left,
	Right
};

//Axes Aligned Bounding Box
struct AABB {
	AABB(const glm::vec2 &a_bottom_left, const glm::vec2 &a_top_right)
		: bottom_left(a_bottom_left)
		, top_right(a_top_right) {}
	glm::vec2 bottom_left;
	glm::vec2 top_right;
};

struct Collider {
	using Callback = std::function<void(const GameObject &, const CollisionDirection)>;

	Collider(const AABB &a_bounding_box, Callback a_collision_callback = {})
		: bounding_box(a_bounding_box)
		, is_active(true)
		, collision_callback(a_collision_callback) {}

	Collider(const glm::vec2 &bottom_left, const glm::vec2 &top_right, Callback a_collision_callback = {})
		: bounding_box(bottom_left, top_right)
		, is_active(true)
		, collision_callback(a_collision_callback) {}

	AABB bounding_box;
	bool is_active;
	Callback collision_callback;
};

class PhysicsEngine {
public:
	~PhysicsEngine() = delete;
	PhysicsEngine() = delete;
	PhysicsEngine(const PhysicsEngine &) = delete;
	PhysicsEngine &operator=(const PhysicsEngine &) = delete;
	PhysicsEngine &operator=(PhysicsEngine &&) = delete;
	PhysicsEngine(PhysicsEngine &&) = delete;

	static void Initialize();
	static void Terminate();

	static void Update(const double delta);
	static void AddDynamicGameObject(std::shared_ptr<GameObject> game_object);
	static void SetCurrentLevel(std::shared_ptr<Level> level);

private:
	static std::unordered_set<std::shared_ptr<GameObject>> dynamic_objects_;
	static std::shared_ptr<Level> level_;
	static bool CheckIntersection(const Collider &collider1, const glm::vec2 &position1,
								  const Collider &collider2, const glm::vec2 &position2);
	static void AlignDynamicObject(std::shared_ptr<GameObject> dynamic_object);
	static std::pair<CollisionDirection, CollisionDirection> GetOppositeCollisionDirections(std::shared_ptr<GameObject> dynamic_object);
};
}