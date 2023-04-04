#ifndef CGFX_MATH_HPP
#define CGFX_MATH_HPP

#include "Core.hpp"

namespace cgfx {

    struct Point2D {

        Point2D() = default;

        Point2D(u32 x, u32 y) : x(x), y(y) {

        }

        u32 x;
        u32 y;
    };

    struct Rect2D {
        constexpr explicit Rect2D(u32 x = 0, u32 y = 0, u32 w = 0, u32 h = 0) :
                position_x(x), position_y(y), width(w), height(h) {
        }

        constexpr u32 GetArea() const {
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

		u32 position_x;
		u32 position_y;
		u32 width;
		u32 height;
    };
}

#endif //CGFX_MATH_HPP
