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
	for (auto &dynamic_object : dynamic_objects_) {
		if (!(dynamic_object->GetVelocity() > 0.)) {
			continue;
		}

		AlignDynamicObject(dynamic_object);

		auto [dynamic_object_collision_direction, object_collision_direction] = GetOppositeCollisionDirections(dynamic_object);

		bool has_collision = false;
		const auto new_position = dynamic_object->GetPosition() +
			dynamic_object->GetDirection() * static_cast<float>(dynamic_object->GetVelocity() * delta);
		const auto &colliders = dynamic_object->GetColliders();
		auto near_objects_to_check = level_->GetObjectsInArea(new_position, new_position + dynamic_object->GetSize());

		for (const auto &dynamic_object_collider : colliders) {
			for (const auto &near_object : near_objects_to_check) {
				const auto &colliders_to_check = near_object->GetColliders();
				if (near_object->CheckCanCollide(dynamic_object->GetType()) && !colliders_to_check.empty()) {
					for (const auto &near_object_collider : near_object->GetColliders()) {
						if (near_object_collider.is_active &&
							CheckIntersection(near_object_collider, new_position, dynamic_object_collider, near_object->GetPosition())) {
							has_collision = true;
							if (near_object_collider.collision_callback) {
								near_object_collider.collision_callback(*dynamic_object, object_collision_direction);
							}
							if (dynamic_object_collider.collision_callback) {
								dynamic_object_collider.collision_callback(*near_object, dynamic_object_collision_direction);
							}
						}
					}
				}
			}
		}

		if (!has_collision) {
			dynamic_object->SetPosition(new_position);
		} else {
			AlignDynamicObject(dynamic_object);
		}
	}
}

void PhysicsEngine::AddDynamicGameObject(std::shared_ptr<GameObject> game_object) {
	dynamic_objects_.insert(std::move(game_object));
}

void PhysicsEngine::SetCurrentLevel(std::shared_ptr<Level> level) {
	level_.swap(level);
}
bool PhysicsEngine::CheckIntersection(const Collider &collider1, const glm::vec2 &position1,
									  const Collider &collider2, const glm::vec2 &position2) {
	const glm::vec2 collider1_bottom_left_world = collider1.bounding_box.bottom_left + position1;
	const glm::vec2 collider1_top_right_world = collider1.bounding_box.top_right + position1;

	const glm::vec2 collider2_bottom_left_world = collider2.bounding_box.bottom_left + position2;
	const glm::vec2 collider2_top_right_world = collider2.bounding_box.top_right + position2;

	if (collider1_bottom_left_world.x >= collider2_top_right_world.x) {
		return false;
	}
	if (collider1_top_right_world.x <= collider2_bottom_left_world.x) {
		return false;
	}
	if (collider1_bottom_left_world.y >= collider2_top_right_world.y) {
		return false;
	}
	if (collider1_top_right_world.y <= collider2_bottom_left_world.y) {
		return false;
	}
	return true;
}

void PhysicsEngine::AlignDynamicObject(std::shared_ptr<GameObject> dynamic_object) {
	if (dynamic_object->GetDirection().x != 0.f) {
		dynamic_object->SetPosition({ dynamic_object->GetPosition().x,
									static_cast<uint32_t>(dynamic_object->GetPosition().y / 4.f + 0.5f) * 4.f });
	} else if (dynamic_object->GetDirection().y != 0.f) {
		dynamic_object->SetPosition({ static_cast<uint32_t>(dynamic_object->GetPosition().x / 4.f + 0.5f) * 4.f,
									dynamic_object->GetPosition().y });
	}
}

std::pair<CollisionDirection, CollisionDirection> PhysicsEngine::GetOppositeCollisionDirections(std::shared_ptr<GameObject> dynamic_object) {
	CollisionDirection main_collision_direction = CollisionDirection::Right;
	CollisionDirection opposite_collision_direction = CollisionDirection::Left;
	if (dynamic_object->GetDirection().x < 0) {
		main_collision_direction = CollisionDirection::Left;
		opposite_collision_direction = CollisionDirection::Right;
	} else if (dynamic_object->GetDirection().y > 0) {
		main_collision_direction = CollisionDirection::Bottom;
		opposite_collision_direction = CollisionDirection::Top;
	} else if (dynamic_object->GetDirection().y < 0) {
		main_collision_direction = CollisionDirection::Top;
		opposite_collision_direction = CollisionDirection::Bottom;
	}
	return { main_collision_direction ,opposite_collision_direction };
}
}