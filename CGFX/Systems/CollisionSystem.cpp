#include "CollisionSystem.hpp"
#include "CGFX/ECS/Components/BoxCollider.hpp"
#include "CGFX/ECS/Components/TransformComponent.hpp"

namespace cgfx {

    CollisionSystem::CollisionSystem() {
        Require<BoxCollider, TransformComponent>();
    }

    void CollisionSystem::UpdateFixed() {
        ForEach<BoxCollider, TransformComponent>([this](Entity entity, const auto& box, const auto& transform) {
            ForEach<BoxCollider, TransformComponent>([&](Entity entity2, const auto& box2, const auto& transform2) {
                if (entity == entity2) {
                    return;
                }
                BoxColliderTransform a(box, transform);
                BoxColliderTransform b(box2, transform2);

                if (AABB(a, b)) {
                    Logger::Info("BoxCollider {},{}", entity, entity2);
                }
            });
        });
    }

    bool CollisionSystem::AABB(const BoxColliderTransform& a, const BoxColliderTransform& b) {
        return (a.transform.position.x < b.transform.position.x + b.box.width &&
                a.transform.position.x + a.box.width > b.transform.position.x &&
                a.transform.position.y < b.transform.position.y + b.box.height &&
                a.transform.position.y + a.box.height > b.transform.position.y);
    }
} // cgfx