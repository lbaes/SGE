#ifndef CGFX_GAME_HPP
#define CGFX_GAME_HPP

#include "SDL.h"
#include "CGFX/Core/Macros.hpp"
#include "CGFX/ECS/ECS.hpp"
#include "CGFX/Assets/AssetStore.hpp"
#include "CGFX/Assets/Texture2D.hpp"

const int FPS = 60;
const int MS_PER_UPDATE = 16;
const int MAX_FRAME_SKIP = 10;

namespace cgfx {
    class Game {
    public:
        Game();
        virtual ~Game();
        DELETE_COPY_AND_ASSIGN(Game);
        DEFAULT_MOVE_AND_ASSIGN(Game);
        void Run();

        virtual void OnGameStart() {};

        virtual void OnGameUpdate(float dt) {};

        virtual void OnGameFixedUpdate() {};

        int GetWidth() const {
            return mWindowWidth;
        }

        int GetHeight() const {
            return mWindowHeight;
        }

        Registry& GetRegistry() {
            return mRegistry;
        }

        AssetStore<Texture2D>& GetTexStore() const {
            return *mTextureStore;
        }

        SDL_Renderer *GetRenderer() const {
            return mRenderer;
        }

    private:
        void Setup();
        void ProcessInput();
        void Update(float dt);
        void UpdateFixed();
        void UpdateRegistry();
        void Render();
        int mWindowWidth;
        int mWindowHeight;
        bool mIsRunning;
        SDL_Window *mWindow;
        SDL_Renderer *mRenderer;
        Registry mRegistry;
        std::shared_ptr<AssetStore<Texture2D>> mTextureStore;
    };
} // cgfx

#endif //CGFX_GAME_HPP
