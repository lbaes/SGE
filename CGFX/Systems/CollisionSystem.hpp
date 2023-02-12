#ifndef CGFX_COLLISIONSYSTEM_HPP
#define CGFX_COLLISIONSYSTEM_HPP

#include "CGFX/ECS/System.hpp"
#include "CGFX/ECS/Components/TransformComponent.hpp"
#include "CGFX/ECS/Components/BoxCollider.hpp"
#include "detail/BoxColliderTransform.hpp"

namespace cgfx {

    class CollisionSystem : public System {
    public:
        explicit CollisionSystem(std::shared_ptr<EventBus> bus);
        void UpdateFixed();
    private:
        static bool AABB(const detail::BoxColliderTransform& a, const detail::BoxColliderTransform& b);
		std::shared_ptr<EventBus> mBus;
    };


} // cgfx

#endif //CGFX_COLLISIONSYSTEM_HPP
