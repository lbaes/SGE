#include "CGFX/Systems/SpriteRenderer.hpp"
#include "CGFX/ECS/Components/SpriteComponent.hpp"
#include "CGFX/ECS/Components/TransformComponent.hpp"
#include "CGFX/ECS/Components/BoxCollider.hpp"

#include <utility>

namespace cgfx {
    SpriteRenderer::
    SpriteRenderer(SDL_Renderer *renderer,
                   std::shared_ptr<AssetStore<Texture2D>> textureStore) :
            mRenderer(renderer), mTextureStore(std::move(textureStore)) {
        Require<SpriteComponent, TransformComponent>();
    }

    void SpriteRenderer::Update() {
        const auto currentNumEntities = GetNumberOfEntitiesOnSystem();
        if (currentNumEntities != previousEntities) {
            SortEntities([&](Entity a, Entity b) {
                const auto& componentA = GetComponent<SpriteComponent>(a);
                const auto& componentB = GetComponent<SpriteComponent>(b);
                return componentA.z_index < componentB.z_index;
            });
            previousEntities = currentNumEntities;
        }

        ForEach<SpriteComponent, TransformComponent>
                ([=](auto& sprite, const auto& transform) {

                    const auto sdlTexture = mTextureStore->Get(sprite.texture_id)->GetSDLTexture();

                    SDL_Rect source_rect;
                    source_rect.x = sprite.source_rect.position_x * sprite.source_rect.height;
                    source_rect.y = sprite.source_rect.position_y * sprite.source_rect.width;
                    source_rect.w = sprite.source_rect.width;
                    source_rect.h = sprite.source_rect.height;

                    SDL_Rect destination_rect;
                    destination_rect.x = static_cast<int>(transform.position.x);
                    destination_rect.y = static_cast<int>(transform.position.y);
                    destination_rect.w = sprite.source_rect.width * static_cast<int>(transform.scale.x);
                    destination_rect.h = sprite.source_rect.height * static_cast<int>(transform.scale.y);

                    SDL_RenderCopyEx(mRenderer, sdlTexture, &source_rect, &destination_rect,
                                     transform.rotation, NULL, SDL_FLIP_NONE);
                });

        ForEach<TransformComponent>([=](auto entity, const auto& transform) {
            if (HasComponent<BoxCollider>(entity)) {
                auto& box = GetComponent<BoxCollider>(entity);
                SDL_Rect debugRect;
                debugRect.x = static_cast<int>(transform.position.x);
                debugRect.y = static_cast<int>(transform.position.y);
                debugRect.w = box.width;
                debugRect.h = box.height;
                SDL_RenderDrawRect(mRenderer, &debugRect);
            }
        });
    }

} // cgfx