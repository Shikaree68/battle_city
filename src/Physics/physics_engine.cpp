#include "physics_engine.h"
#include "../Game/GameObjects/game_object_interface.h"

std::unordered_set<std::shared_ptr<GameObject>> PhysicsEngine::dynamic_objects_;

void PhysicsEngine::Initialize() {}

void PhysicsEngine::Terminate() {
	dynamic_objects_.clear();
}

void PhysicsEngine::Update(const double delta) {
	for(auto& current_object : dynamic_objects_) {
		if(current_object->GetVelocity() > 0) {
			current_object->GetPosition() +=
				current_object->GetDirection() *
				static_cast<float>(current_object->GetVelocity() * delta);
		}
	}
}

void PhysicsEngine::AddDynamicGameObject(std::shared_ptr<GameObject> game_object) {
	dynamic_objects_.insert(std::move(game_object));
}
