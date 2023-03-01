#ifndef CGFX_SPRITERENDERER_HPP
#define CGFX_SPRITERENDERER_HPP

#include "SDL.h"
#include "CGFX/ECS/ECS.hpp"
#include "CGFX/Assets/AssetStore.hpp"
#include "CGFX/Assets/Texture2D.hpp"
#include "CGFX/Core/Camera2D.hpp"

namespace cgfx {

    class SpriteRenderer final : public System {
    public:
        explicit SpriteRenderer(SDL_Renderer *renderer, const Camera2D& camera,
                                std::shared_ptr<AssetStore<Texture2D>> textureStore);
        void Update();
    private:
        SDL_Renderer *mRenderer;
		const Camera2D& mCamera;
        std::shared_ptr<AssetStore<Texture2D>> mTextureStore;
	};

    ENABLE_TYPENAME(SpriteRenderer);
} // cgfx

#endif //CGFX_SPRITERENDERER_HPP
