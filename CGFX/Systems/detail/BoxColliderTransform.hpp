
#ifndef CGFX_BOXCOLLIDERTRANSFORM_HPP
#define CGFX_BOXCOLLIDERTRANSFORM_HPP

#include "CGFX/ECS/Components/BoxCollider.hpp"
#include "CGFX/ECS/Components/TransformComponent.hpp"

namespace cgfx::detail {
    struct BoxColliderTransform {
        BoxColliderTransform(const BoxCollider& b, const TransformComponent& t)
                : box(b), transform(t) {
        }

        const BoxCollider& box;
        const TransformComponent& transform;
    };
}
#endif //CGFX_BOXCOLLIDERTRANSFORM_HPP
