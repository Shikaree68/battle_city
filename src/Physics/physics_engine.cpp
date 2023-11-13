#include "physics_engine.h"
#include "../Game/GameObjects/game_object_interface.h"
#include "../Game/level.h"

namespace Physics {
std::unordered_set<std::shared_ptr<GameObject>> PhysicsEngine::dynamic_objects_;
std::shared_ptr<Level> PhysicsEngine::level_;

void PhysicsEngine::Initialize() {}

void PhysicsEngine::Terminate() {
	dynamic_objects_.clear();
	level_.reset();
}

void PhysicsEngine::Update(const double delta) {
	for(auto& current_object : dynamic_objects_) {
		if(current_object->GetVelocity() > 0) {
			if(current_object->GetDirection().x != 0.f) {
				current_object->GetPosition() = glm::vec2(current_object->GetPosition().x,
														  static_cast<uint32_t>(current_object->GetPosition().y / 4.f + 0.5f) * 4.f);
			} else if(current_object->GetDirection().y != 0.f) {
				current_object->GetPosition() = glm::vec2(static_cast<uint32_t>(current_object->GetPosition().x / 4.f + 0.5f) * 4.f,
														  current_object->GetPosition().y);
			}

			const auto new_position = current_object->GetPosition() +
				current_object->GetDirection() *
				static_cast<float>(current_object->GetVelocity() * delta);
			const auto& colliders = current_object->GetColliders();
			auto near_objects = level_->GetObjectsInArea(new_position, new_position + current_object->GetSize());

			bool has_collision = false;

			for(const auto& current_near_object : near_objects) {
				const auto& colliders_to_check = current_near_object->GetColliders();
				if(!colliders_to_check.empty()) {
					if(CheckIntersection(colliders, new_position, colliders_to_check, current_near_object->GetPosition())) {
						has_collision = true;
						break;
					}
				}
			}

			if(!has_collision) {
				current_object->GetPosition() = new_position;
			} else {
				if(current_object->GetDirection().x != 0.f) {
					current_object->GetPosition() = glm::vec2(static_cast<uint32_t>(current_object->GetPosition().x / 8.f + 0.5f) * 8.f,
															  current_object->GetPosition().y);
				} else if(current_object->GetDirection().y != 0.f) {
					current_object->GetPosition() = glm::vec2(current_object->GetPosition().x,
															  static_cast<uint32_t>(current_object->GetPosition().y / 8.f + 0.5f) * 8.f);
				}
			}

		}
	}
}

void PhysicsEngine::AddDynamicGameObject(std::shared_ptr<GameObject> game_object) {
	dynamic_objects_.insert(std::move(game_object));
}

void PhysicsEngine::SetCurrentLevel(std::shared_ptr<Level> level) {
	level_.swap(level);
}
bool PhysicsEngine::CheckIntersection(const std::vector<AABB>& colliders1, const glm::vec2& position1, const std::vector<AABB>& colliders2, const glm::vec2& position2) {
	for(const auto& collider1 : colliders1) {
		const glm::vec2 collider1_bottom_left_world = collider1.bottom_left + position1;
		const glm::vec2 collider1_top_right_world = collider1.top_right + position1;
		for(const auto& collider2 : colliders2) {
			const glm::vec2 collider2_bottom_left_world = collider2.bottom_left + position2;
			const glm::vec2 collider2_top_right_world = collider2.top_right + position2;

			if(collider1_bottom_left_world.x >= collider2_top_right_world.x) {
				return false;
			}
			if(collider1_top_right_world.x <= collider2_bottom_left_world.x) {
				return false;
			}

			if(collider1_bottom_left_world.y >= collider2_top_right_world.y) {
				return false;
			}

			if(collider1_top_right_world.y <= collider2_bottom_left_world.y) {
				return false;
			}
			return true;
		}
	}
}
}