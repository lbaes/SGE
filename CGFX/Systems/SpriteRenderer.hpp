#ifndef CGFX_SPRITERENDERER_HPP
#define CGFX_SPRITERENDERER_HPP

#include "SDL.h"
#include "CGFX/ECS/ECS.hpp"
#include "CGFX/Assets/AssetStore.hpp"
#include "CGFX/Assets/Texture2D.hpp"

namespace cgfx {

    class SpriteRenderer final : public System {
    public:
        explicit SpriteRenderer(SDL_Renderer *renderer,
                                std::shared_ptr<AssetStore<Texture2D>> textureStore);
        void Update();
    private:
        SDL_Renderer *mRenderer;
        std::shared_ptr<AssetStore<Texture2D>> mTextureStore;
        size_t previousEntities = 0;
    };

    ENABLE_TYPENAME(SpriteRenderer);
} // cgfx

#endif //CGFX_SPRITERENDERER_HPP
