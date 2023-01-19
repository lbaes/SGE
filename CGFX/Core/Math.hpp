#ifndef CGFX_MATH_HPP
#define CGFX_MATH_HPP

#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"

namespace cgfx {

    using vec2 = glm::vec2;
    using vec3 = glm::vec3;
    using vec4 = glm::vec4;

    struct Point2D {

        Point2D() = default;

        Point2D(uint32_t x, uint32_t y) : x(x), y(y) {

        }

        uint32_t x;
        uint32_t y;
    };

    struct Rect2D {
        constexpr explicit Rect2D(uint32_t x = 0, uint32_t y = 0, uint32_t w = 0, uint32_t h = 0) :
                position_x(x), position_y(y), width(w), height(h) {
        }

        constexpr uint32_t GetArea() const {
            return width * height;
        }

        bool operator==(const Rect2D& rhs) const {
            return position_x == rhs.position_x &&
                   position_y == rhs.position_y &&
                   width == rhs.width &&
                   height == rhs.height;
        }

        bool operator!=(const Rect2D& rhs) const {
            return !(rhs == *this);
        }

        uint32_t position_x;
        uint32_t position_y;
        uint32_t width;
        uint32_t height;
    };
}

#endif //CGFX_MATH_HPP
