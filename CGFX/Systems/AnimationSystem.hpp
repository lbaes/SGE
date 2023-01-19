#ifndef CGFX_ANIMATIONSYSTEM_HPP
#define CGFX_ANIMATIONSYSTEM_HPP

#include "CGFX/ECS/System.hpp"
#include "CGFX/ECS/Components/SpriteComponent.hpp"

namespace cgfx {

    class AnimationSystem final : public System {
    public:
        AnimationSystem();
        void UpdateFixed();
        void Update(float deltaTime);
    };

} // cgfx

#endif //CGFX_ANIMATIONSYSTEM_HPP
