#ifndef CGFX_PHYSICSSYSTEM_HPP
#define CGFX_PHYSICSSYSTEM_HPP

#include "CGFX/Core/Core.hpp"
#include "CGFX/ECS/Registry.hpp"
#include "CGFX/ECS/System.hpp"
#include "CGFX/ECS/Components/TransformComponent.hpp"
#include "CGFX/ECS/Components/RigidBodyComponent.hpp"

namespace cgfx {

    class PhysicsSystem final : public System {
    public:
        PhysicsSystem(std::shared_ptr<EventBus> eventBus);
        void UpdateFixed();
    private:
		std::shared_ptr<EventBus> mBus;
    };

    ENABLE_TYPENAME(PhysicsSystem)
} // cgfx

#endif //CGFX_PHYSICSSYSTEM_HPP
