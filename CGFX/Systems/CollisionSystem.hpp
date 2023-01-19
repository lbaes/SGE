#ifndef CGFX_COLLISIONSYSTEM_HPP
#define CGFX_COLLISIONSYSTEM_HPP

#include "CGFX/ECS/System.hpp"
#include "CGFX/ECS/Components/TransformComponent.hpp"
#include "CGFX/ECS/Components/BoxCollider.hpp"

namespace cgfx {

    struct BoxColliderTransform {
        BoxColliderTransform(const BoxCollider& b, const TransformComponent& t)
                : box(b), transform(t) {

        }

        const BoxCollider& box;
        const TransformComponent& transform;
    };

    class CollisionSystem : public System {
    public:
        CollisionSystem();
        void UpdateFixed();
    private:
        static bool AABB(const BoxColliderTransform& a, const BoxColliderTransform& b);
    };

} // cgfx

#endif //CGFX_COLLISIONSYSTEM_HPP
