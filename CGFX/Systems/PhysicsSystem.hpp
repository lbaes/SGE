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
        PhysicsSystem();
        void UpdateFixed();
        void Update(float deltaTime);
    private:
    };

    ENABLE_TYPENAME(PhysicsSystem);
} // cgfx

#endif //CGFX_PHYSICSSYSTEM_HPP
