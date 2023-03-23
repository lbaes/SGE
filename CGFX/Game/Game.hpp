#ifndef CGFX_GAME_HPP
#define CGFX_GAME_HPP

#include "SDL.h"
#include "CGFX/Core/Macros.hpp"
#include "CGFX/Core/Keys.hpp"
#include "CGFX/Core/Camera2D.hpp"
#include "CGFX/ECS/ECS.hpp"
#include "CGFX/Assets/AssetStore.hpp"
#include "CGFX/Assets/Texture2D.hpp"
#include "imgui.h"
#include "backends/imgui_impl_sdl2.h"
#include "backends/imgui_impl_sdlrenderer.h"

namespace cgfx {
    class Game {
    public:
        Game();
		Game(int windowWidth, int windowHeight);
        virtual ~Game();
        DELETE_COPY_AND_ASSIGN(Game);
        DEFAULT_MOVE_AND_ASSIGN(Game);
        void Run();

        virtual void OnGameStart() {};

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

		EventBus& GetBus() const {
			return *mEventBus;
		}

        AssetStore<Texture2D>& GetTexStore() const {
            return *mTextureStore;
        }

        SDL_Renderer *GetRenderer() const {
            return mRenderer;
        }

		const static float deltaTime;

	protected:
		static std::string GetResource(const std::string& filename, const std::string& type);

    private:
        void Setup();
        void ProcessInput();
        void FixedUpdate();
        void UpdateRegistry();
        void Render();
        int mWindowWidth;
        int mWindowHeight;
		int mRenderWidth;
		int mRenderHeight;
        bool mIsRunning;
        SDL_Window *mWindow;
        SDL_Renderer *mRenderer;
        Registry mRegistry;
        std::shared_ptr<AssetStore<Texture2D>> mTextureStore;
		std::shared_ptr<EventBus> mEventBus;
        Logger logger{"ENGINE"};
		Camera2D camera{};
		ImGuiIO* io = nullptr;
		bool show_demo_window = true;

		void DispatchEvents(SDL_KeyCode sdlKey, KeyState state);
    };
} // cgfx

#endif //CGFX_GAME_HPP
