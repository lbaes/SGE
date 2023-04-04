#ifndef CGFX_RIGIDBODYCOMPONENT_HPP
#define CGFX_RIGIDBODYCOMPONENT_HPP

#include "glm/vec2.hpp"

namespace cgfx {

    struct RigidBodyComponent {
        explicit RigidBodyComponent(f32 xv = 0, f32 yv = 0, f32 xa = 0.0f, f32 ya = 0.0f) :
			acceleration(xa, ya),
			velocity(xv, yv) {}

		glm::vec2 acceleration;
        glm::vec2 velocity;
    };

    ENABLE_TYPENAME(RigidBodyComponent)

} // cgfx

#endif //CGFX_RIGIDBODYCOMPONENT_HPP
