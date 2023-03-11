#ifndef CGFX_RIGIDBODYCOMPONENT_HPP
#define CGFX_RIGIDBODYCOMPONENT_HPP

#include "glm/vec2.hpp"

namespace cgfx {

    struct RigidBodyComponent {
        explicit RigidBodyComponent(float xv = 0, float yv = 0, float xa = 0.0f, float ya = 0.0f) :
			acceleration(xa, ya),
			velocity(xv, yv) {}

		glm::vec2 acceleration;
        glm::vec2 velocity;
    };

    ENABLE_TYPENAME(RigidBodyComponent);

} // cgfx

#endif //CGFX_RIGIDBODYCOMPONENT_HPP
