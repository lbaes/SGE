#include "AnimationSystem.hpp"
#include "SDL_timer.h"

namespace cgfx {
    AnimationSystem::AnimationSystem() : System() {
        Require<SpriteComponent, SpriteAnimationComponent>();
    }

    void AnimationSystem::UpdateFixed() {
        // logger->Info("[ANIMATION] Update Fixed");
        ForEach<SpriteComponent, SpriteAnimationComponent>(
                [=](auto& sprite, auto& animation) {

                    float dt = (SDL_GetTicks64() - animation.last_update) / 1000.0f;
                    int framesToUpdate = floor(dt / (1.0f / animation.speed));
                    if (framesToUpdate > 0) {
                        animation.current_frame += framesToUpdate;
                        animation.current_frame %= animation.max_frames;
                        sprite.source_rect.position_x = animation.current_frame;
                        animation.last_update = SDL_GetTicks64();
                    }
                });
    }

    void AnimationSystem::Update(float deltaTime) {
        //logger->Info("[ANIMATION] Update Variable: {}", deltaTime);
    }
} // cgfx