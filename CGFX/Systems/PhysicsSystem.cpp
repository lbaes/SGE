#include "CGFX/Systems/PhysicsSystem.hpp"
#include "CGFX/Game/Game.hpp"

namespace cgfx {

PhysicsSystem::PhysicsSystem(std::shared_ptr<EventBus> eventBus)
    : System(), mBus(std::move(eventBus)) {
  Require<TransformComponent, RigidBodyComponent>();
}

void PhysicsSystem::UpdateFixed() {
  ForEach<TransformComponent, RigidBodyComponent>(
      [](auto entity, auto &transform, auto &rigid) {
        rigid.velocity += rigid.acceleration * Game::deltaTime;
        transform.position += rigid.velocity * Game::deltaTime;
      });
}

} // namespace cgfx