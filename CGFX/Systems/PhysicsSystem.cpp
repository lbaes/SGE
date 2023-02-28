#include "CGFX/Systems/PhysicsSystem.hpp"

namespace cgfx {

    PhysicsSystem::PhysicsSystem() : System() {
        Require<TransformComponent, RigidBodyComponent>();
    }

    void PhysicsSystem::UpdateFixed() {
        ForEach<TransformComponent, RigidBodyComponent>(
                [](auto& transform, auto& rigid) {
					if (rigid.velocity.x >= 3){

					}
                    transform.position += rigid.velocity;
                });
    }

    void PhysicsSystem::Update(float deltaTime) {

    }

} // cgfx