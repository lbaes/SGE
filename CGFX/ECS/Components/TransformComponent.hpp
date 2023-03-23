#ifndef CGFX_TRANSFORMCOMPONENT_HPP
#define CGFX_TRANSFORMCOMPONENT_HPP

#include "CGFX/Core/Reflection.hpp"
#include "glm/vec2.hpp"

namespace cgfx {

    struct TransformComponent {
        TransformComponent() : position(0, 0), scale(1, 1), rotation(0.0f) {
        }

        TransformComponent(int x, int y, int scale_w = 1, int scale_h = 1, float rotation = 0.0f)
            : position(x, y), scale(scale_w, scale_h), rotation(rotation) {

        }

        glm::vec2 position;
        glm::vec2 scale;
        float rotation;
    };

    ENABLE_TYPENAME(TransformComponent)

} // cgfx

#endif //CGFX_TRANSFORMCOMPONENT_HPP
