#pragma once
#include <unordered_set>
#include <memory>

class GameObject;

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

private:
	static std::unordered_set<std::shared_ptr<GameObject>> dynamic_objects_;

};