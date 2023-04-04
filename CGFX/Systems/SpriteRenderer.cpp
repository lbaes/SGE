#include "CGFX/Systems/SpriteRenderer.hpp"
#include "CGFX/ECS/Components/SpriteComponent.hpp"
#include "CGFX/ECS/Components/TransformComponent.hpp"
#include "CGFX/ECS/Components/BoxCollider.hpp"
#include "CGFX/ECS/Components/DebugComponent.hpp"

#include <utility>

namespace cgfx {
    SpriteRenderer::
    SpriteRenderer(SDL_Renderer *renderer, const Camera2D& camera, std::shared_ptr<AssetStore<Texture2D>> textureStore) :
            mRenderer(renderer), mCamera(camera), mTextureStore(std::move(textureStore)) {
        Require<SpriteComponent, TransformComponent>();
    }

    void SpriteRenderer::Update() {
        ForEach<SpriteComponent, TransformComponent>
                ([=](auto& sprite, const auto& transform) {

                    const auto sdlTexture = mTextureStore->Get(sprite.texture_id)->GetSDLTexture();

                    SDL_Rect source_rect;
                    source_rect.x = sprite.source_rect.position_x * sprite.source_rect.height;
                    source_rect.y = sprite.source_rect.position_y * sprite.source_rect.width;
                    source_rect.w = sprite.source_rect.width;
                    source_rect.h = sprite.source_rect.height;

                    SDL_Rect destination_rect;
                    destination_rect.x = static_cast<i32>(transform.position.x - mCamera.position_x);
                    destination_rect.y = static_cast<i32>(transform.position.y - mCamera.position_y);
                    destination_rect.w = sprite.source_rect.width * static_cast<i32>(transform.scale.x);
                    destination_rect.h = sprite.source_rect.height * static_cast<i32>(transform.scale.y);

                    SDL_RenderCopyEx(mRenderer, sdlTexture, &source_rect, &destination_rect,
                                     transform.rotation, NULL, SDL_FLIP_NONE);
                });

        ForEach<TransformComponent>([=](auto entity, const auto& transform) {
            if (HasComponent<BoxCollider>(entity) && HasComponent<DebugComponent>(entity)) {
                auto& box = GetComponent<BoxCollider>(entity);
                SDL_Rect debugRect;
                debugRect.x = static_cast<i32>(transform.position.x - mCamera.position_x);
                debugRect.y = static_cast<i32>(transform.position.y - mCamera.position_y);
                debugRect.w = box.width;
                debugRect.h = box.height;
                SDL_RenderDrawRect(mRenderer, &debugRect);
            }
        });
    }

} // cgfx