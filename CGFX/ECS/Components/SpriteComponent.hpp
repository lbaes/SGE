#ifndef CGFX_SPRITECOMPONENT_HPP
#define CGFX_SPRITECOMPONENT_HPP

#include <string>
#include "CGFX/Core/StringId.hpp"
#include "CGFX/Core/Math.hpp"

namespace cgfx {

    struct SpriteComponent {
        SpriteComponent(const std::string& assetName, Rect2D sourceRect, int32_t zIndex = 0)
                : texture_id(MakeStringId(assetName)), source_rect(sourceRect), z_index(zIndex) {
        }

        StringId texture_id = 0;
        Rect2D source_rect{};
        int32_t z_index = 0;
    };

    struct SpriteAnimationComponent {
        int current_frame = 0;
        int max_frames = 1;
        uint64_t last_update = 0;
        int speed = 1;
        bool loop = false;
		int updates = 0;
	};

    ENABLE_TYPENAME(SpriteComponent)
    ENABLE_TYPENAME(SpriteAnimationComponent)

} // cgfx

#endif //CGFX_SPRITECOMPONENT_HPP
