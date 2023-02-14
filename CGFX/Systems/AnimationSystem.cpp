#include "AnimationSystem.hpp"
#include "SDL_timer.h"

namespace cgfx {
    AnimationSystem::AnimationSystem() : System() {
        Require<SpriteComponent, SpriteAnimationComponent>();
    }

    void AnimationSystem::UpdateFixed() {
        ForEach<SpriteComponent, SpriteAnimationComponent>(
                [=](auto& sprite, auto& animation) {

					if (!animation.loop && animation.updates >= animation.max_frames)
						return;

                    float dt = (SDL_GetTicks64() - animation.last_update) / 1000.0f;
                    int framesToUpdate = static_cast<int>(floor(dt / (1.0f / animation.speed)));
                    if (framesToUpdate > 0) {
                        animation.current_frame += framesToUpdate;
                        animation.current_frame %= animation.max_frames;
                        sprite.source_rect.position_x = animation.current_frame;
                        animation.last_update = SDL_GetTicks64();
						animation.updates++;
                    }
                });
    }

    void AnimationSystem::Update(float deltaTime) {

    }
} // cgfx