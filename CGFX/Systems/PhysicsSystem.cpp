#include "CGFX/Systems/PhysicsSystem.hpp"
#include "CGFX/Game/Game.hpp"

namespace cgfx {

    PhysicsSystem::PhysicsSystem() : System() {
        Require<TransformComponent, RigidBodyComponent>();
    }

    void PhysicsSystem::UpdateFixed() {
        ForEach<TransformComponent, RigidBodyComponent>(
                [](auto& transform, auto& rigid) {
					rigid.velocity 	+= rigid.acceleration * Game::deltaTime;
				    transform.position += rigid.velocity  * Game::deltaTime;
				});
    }

} // cgfx