#include "CollisionSystem.hpp"

namespace cgfx {

    CollisionSystem::CollisionSystem() {
        Require<BoxCollider, TransformComponent>();
    }

    void CollisionSystem::UpdateFixed() {
        auto first = begin();
        auto last = end();
        int comps = 0;

        ForEach<BoxCollider, TransformComponent>(first, last,
        [this, &first, &last, &comps](Entity entity, const auto& b, const auto& t) {
            first++;
            ForEach<BoxCollider, TransformComponent>(first, last,
                [&entity, &b, &t, &comps](Entity entity2, const auto& b2, const auto& t2) {
                    detail::BoxColliderTransform bct(b, t);
                    detail::BoxColliderTransform bct2(b2, t2);

                    if (AABB(bct, bct2)) {
						(void)entity;
						(void)entity2;
						//TODO CollisionCallback
                    }
                    comps++;
                });
        });
    }

    bool CollisionSystem::AABB(const detail::BoxColliderTransform& a, const detail::BoxColliderTransform& b) {
        return (a.transform.position.x < b.transform.position.x + b.box.width &&
                a.transform.position.x + a.box.width > b.transform.position.x &&
                a.transform.position.y < b.transform.position.y + b.box.height &&
                a.transform.position.y + a.box.height > b.transform.position.y);
    }

} // cgfx