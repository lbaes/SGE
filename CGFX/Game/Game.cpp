#include <array>
#include "Game.hpp"
#include "CGFX/Systems/PhysicsSystem.hpp"
#include "CGFX/Systems/SpriteRenderer.hpp"
#include "CGFX/Systems/AnimationSystem.hpp"
#include "CGFX/Systems/CollisionSystem.hpp"

namespace cgfx {

    Game::Game() :
            mWindowWidth(0),
            mWindowHeight(0),
            mIsRunning(false),
            mWindow(nullptr),
            mRenderer(nullptr),
            mTextureStore(std::make_shared<AssetStore<Texture2D>>()) {


        if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
            return;
        }

        mWindow = SDL_CreateWindow("CGFX",
                                   SDL_WINDOWPOS_CENTERED,
                                   SDL_WINDOWPOS_CENTERED,
                                   800,
                                   600, SDL_WINDOW_SHOWN);

        if (mWindow == nullptr) {
            return;
        }

        mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_PRESENTVSYNC);
        if (!mRenderer) {
            return;
        }

        SDL_GetRendererOutputSize(mRenderer, &mWindowWidth, &mWindowHeight);
        SDL_RenderSetLogicalSize(mRenderer, mWindowWidth, mWindowHeight);

        constexpr std::array<int, 4> bg = {120, 70, 200, 255};
        SDL_SetRenderDrawColor(mRenderer, bg[0], bg[1], bg[2], bg[3]);
    }

    Game::~Game() {
        SDL_DestroyRenderer(mRenderer);
        SDL_DestroyWindow(mWindow);
        SDL_Quit();
    }

    void Game::Setup() {
        mRegistry.RegisterSystem<PhysicsSystem>();
        mRegistry.RegisterSystem<AnimationSystem>();
        mRegistry.RegisterSystem<CollisionSystem>();
        mRegistry.RegisterSystem<SpriteRenderer>(mRenderer, mTextureStore);
        mRegistry.Update();
    }

    void Game::ProcessInput() {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    mIsRunning = false;
                    return;
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_ESCAPE) {
                        mIsRunning = false;
                    }
                default:
                    break;
            }
        }
    }

    void Game::Update(float dt) {
        mRegistry.GetSystem<PhysicsSystem>().Update(dt);
        mRegistry.GetSystem<AnimationSystem>().Update(dt);
        OnGameUpdate(dt);
    }

    void Game::UpdateFixed() {
        mRegistry.GetSystem<PhysicsSystem>().UpdateFixed();
        mRegistry.GetSystem<AnimationSystem>().UpdateFixed();
        mRegistry.GetSystem<CollisionSystem>().UpdateFixed();
        OnGameFixedUpdate();
    }

    void Game::Render() {
        SDL_RenderClear(mRenderer);
        mRegistry.GetSystem<SpriteRenderer>().Update();
        SDL_RenderPresent(mRenderer);
    }

    void Game::UpdateRegistry() {
        mRegistry.Update();
    }

    void Game::Run() {

        auto get_high_res_time = []() {
            return static_cast<double>(SDL_GetTicks64());
        };

        mIsRunning = true;
        Setup();
        OnGameStart();
        UpdateRegistry();

        double previous = get_high_res_time();
        double lag = 0.0;

        while (mIsRunning) {
            double current = get_high_res_time();
            double elapsed = current - previous;
            previous = current;
            lag += elapsed;

            ProcessInput();
            UpdateRegistry();

            Update(static_cast<float>(elapsed));
            OnGameUpdate(static_cast<float>(elapsed));

            auto updates = 1;
            while (lag >= MS_PER_UPDATE) {
                UpdateFixed();
                OnGameFixedUpdate();
                lag -= MS_PER_UPDATE;
                if (updates++ >= MAX_FRAME_SKIP) {
                    break;
                };
            }

            Render();
        }
    }

} // cgfx