#ifndef CGFX_BOXCOLLIDER_HPP
#define CGFX_BOXCOLLIDER_HPP

#include "CGFX/Core/Math.hpp"

namespace cgfx {

    struct BoxCollider {

        BoxCollider() : BoxCollider(0, 0) {

        }

        BoxCollider(u32 width, u32 height) :
                BoxCollider(width, height, 0, 0) {

        }

        BoxCollider(u32 width, u32 height,
                    u32 offset_x, u32 offset_y) :
                width(width), height(height), offset_x(offset_x), offset_y(offset_y) {

        }

        bool operator==(const BoxCollider& rhs) const {
            return width == rhs.width &&
                   height == rhs.height &&
                   offset_x == rhs.offset_x &&
                   offset_y == rhs.offset_y;
        }

        bool operator!=(const BoxCollider& rhs) const {
            return !(rhs == *this);
        }

        u32 width;
        u32 height;
        u32 offset_x;
        u32 offset_y;
    };

    ENABLE_TYPENAME(BoxCollider)

} // cgfx

#endif //CGFX_BOXCOLLIDER_HPP
