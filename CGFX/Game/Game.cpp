#include <array>
#include <fstream>

#ifdef CGFX_APPLE

#include <corefoundation/CFBundle.h>

#endif

#include "Game.hpp"
#include "CGFX/Systems/PhysicsSystem.hpp"
#include "CGFX/Systems/SpriteRenderer.hpp"
#include "CGFX/Systems/AnimationSystem.hpp"
#include "CGFX/Systems/CollisionSystem.hpp"
#include "CGFX/Event/Events/InputEvents.hpp"
#include "CGFX/Systems/InputLoggerSystem.hpp"
#include "CGFX/Systems/KeyboardControlSystem.hpp"
#include "CGFX/Systems/CameraSystem.hpp"

namespace cgfx {

	const f32 Game::deltaTime = 0.01f;

	Game::Game() : Game(800, 600) {

	}

	Game::Game(int windowWidth, int windowHeight) :
			mWindowWidth(windowWidth),
			mWindowHeight(windowHeight),
			mIsRunning(false),
			mWindow(nullptr),
			mRenderer(nullptr),
			mTextureStore(std::make_shared<AssetStore<Texture2D>>()),
			mEventBus(std::make_shared<EventBus>()), camera() {

		if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
			return;
		}

		mWindow = SDL_CreateWindow("CGFX",
								   SDL_WINDOWPOS_CENTERED,
								   SDL_WINDOWPOS_CENTERED,
								   mWindowWidth,
								   mWindowHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI);

		if (mWindow == nullptr) {
			return;
		}

		mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);
		if (!mRenderer) {
			return;
		}

		SDL_GetRendererOutputSize(mRenderer, &mRenderWidth, &mRenderHeight);
		SDL_RenderSetLogicalSize(mRenderer, mWindowWidth, mWindowHeight);

		logger.Info("Renderer Width and Height: {},{}", mWindowWidth, mWindowHeight);
		camera.position_x = 0;
		camera.position_y = 0;
		camera.width = mWindowWidth;
		camera.height = mWindowHeight;

		constexpr std::array<uint8_t, 4> bg = {120, 70, 200, 255};
		SDL_SetRenderDrawColor(mRenderer, bg[0], bg[1], bg[2], bg[3]);

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGui::StyleColorsDark();
		io = &ImGui::GetIO();

		ImGui_ImplSDL2_InitForSDLRenderer(mWindow, mRenderer);
		ImGui_ImplSDLRenderer_Init(mRenderer);
	}

	Game::~Game() {
		ImGui_ImplSDLRenderer_Shutdown();
		ImGui_ImplSDL2_Shutdown();
		ImGui::DestroyContext();

		SDL_DestroyRenderer(mRenderer);
		SDL_DestroyWindow(mWindow);
		SDL_Quit();
	}

	void Game::Setup() {
		mRegistry.RegisterSystem<PhysicsSystem>(mEventBus);
		mRegistry.RegisterSystem<AnimationSystem>();
		mRegistry.RegisterSystem<CameraSystem>(camera, Rect2D(0, 0, mWindowWidth, mWindowHeight));
		mRegistry.RegisterSystem<KeyboardControlSystem>(mEventBus);
		mRegistry.RegisterSystem<InputLoggerSystem>(mEventBus, std::make_shared<Logger>("Key Logger"));
		mRegistry.RegisterSystem<CollisionSystem>(mEventBus);
		mRegistry.RegisterSystem<SpriteRenderer>(mRenderer, camera, mTextureStore);
		mRegistry.Update();
	}

	void Game::ProcessInput() {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			ImGui_ImplSDL2_ProcessEvent(&event);
			switch (event.type) {
				case SDL_QUIT:
					mIsRunning = false;
					return;
				case SDL_KEYDOWN:
					if (event.key.repeat != 0) {
						DispatchEvents(static_cast<SDL_KeyCode>(event.key.keysym.sym), KeyState::REPEAT);
					} else {
						DispatchEvents(static_cast<SDL_KeyCode>(event.key.keysym.sym), KeyState::PRESSED);
					}

					if (event.key.keysym.sym == SDLK_ESCAPE) {
						mIsRunning = false;
					}
					break;
				case SDL_KEYUP:
					DispatchEvents(static_cast<SDL_KeyCode>(event.key.keysym.sym), KeyState::RELEASED);
					break;
				default:
					break;
			}
		}
	}

	void Game::FixedUpdate() {
		mRegistry.GetSystem<PhysicsSystem>().UpdateFixed();
		mRegistry.GetSystem<CameraSystem>().UpdateFixed();
		mRegistry.GetSystem<AnimationSystem>().UpdateFixed();
		mRegistry.GetSystem<CollisionSystem>().UpdateFixed();
		mRegistry.Update();
		OnGameFixedUpdate();
	}

	void Game::Render() {
		// Rendering
		// Start the Dear ImGui frame
		ImGui_ImplSDLRenderer_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();
		// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
		if (show_demo_window)
			ImGui::ShowDemoWindow(&show_demo_window);
		ImGui::Render();
		SDL_RenderSetScale(mRenderer, io->DisplayFramebufferScale.x, io->DisplayFramebufferScale.y);
		SDL_RenderClear(mRenderer);
		mRegistry.GetSystem<SpriteRenderer>().Update();
		ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
		SDL_RenderPresent(mRenderer);
	}

	void Game::UpdateRegistry() {
		mRegistry.Update();
	}

	void Game::Run() {

		auto hires_time_in_seconds = []() {
		  return (static_cast<double>(SDL_GetTicks64()) / 1000.0f);
		};

		mIsRunning = true;
		Setup();
		OnGameStart();
		UpdateRegistry();

		double t = 0.0;
		const double dt = Game::deltaTime;

		double currentTime = hires_time_in_seconds();
		double accumulator = 0.0;

		while (mIsRunning) {
			double newTime = hires_time_in_seconds();
			double frameTime = newTime - currentTime;
			currentTime = newTime;
			accumulator += frameTime;

			ProcessInput();

			while (accumulator >= dt) {
				FixedUpdate();
				accumulator -= dt;
				t += dt;
			}

			Render();
		}
	}

	void Game::DispatchEvents(SDL_KeyCode sdlKey, KeyState keyState) {
		auto key = Key::UNKNOWN;
		switch (sdlKey) {
			case SDLK_UNKNOWN:
				key = Key::UNKNOWN;
				break;
			case SDLK_RETURN:
				key = Key::ENTER;
				break;
			case SDLK_ESCAPE:
				key = Key::ESCAPE;
				break;
			case SDLK_BACKSPACE:
				key = Key::BACKSPACE;
				break;
			case SDLK_TAB:
				key = Key::TAB;
				break;
			case SDLK_SPACE:
				key = Key::SPACE;
				break;
			case SDLK_EXCLAIM:
				break;
			case SDLK_QUOTEDBL:
				break;
			case SDLK_HASH:
				break;
			case SDLK_PERCENT:
				break;
			case SDLK_DOLLAR:
				break;
			case SDLK_AMPERSAND:
				break;
			case SDLK_QUOTE:
				break;
			case SDLK_LEFTPAREN:
				break;
			case SDLK_RIGHTPAREN:
				break;
			case SDLK_ASTERISK:
				break;
			case SDLK_PLUS:
				break;
			case SDLK_COMMA:
				break;
			case SDLK_MINUS:
				break;
			case SDLK_PERIOD:
				break;
			case SDLK_SLASH:
				break;
			case SDLK_0:
				key = Key::K_0;
				break;
			case SDLK_1:
				key = Key::K_1;
				break;
			case SDLK_2:
				key = Key::K_2;
				break;
			case SDLK_3:
				key = Key::K_3;
				break;
			case SDLK_4:
				key = Key::K_4;
				break;
			case SDLK_5:
				key = Key::K_5;
				break;
			case SDLK_6:
				key = Key::K_6;
				break;
			case SDLK_7:
				key = Key::K_7;
				break;
			case SDLK_8:
				key = Key::K_8;
				break;
			case SDLK_9:
				key = Key::K_9;
				break;
			case SDLK_COLON:
				break;
			case SDLK_SEMICOLON:
				key = Key::SEMICOLON;
				break;
			case SDLK_LESS:
				break;
			case SDLK_EQUALS:
				key = Key::EQUAL;
				break;
			case SDLK_GREATER:
				break;
			case SDLK_QUESTION:
				break;
			case SDLK_AT:
				break;
			case SDLK_LEFTBRACKET:
				key = Key::LEFT_BRACKET;
				break;
			case SDLK_BACKSLASH:
				key = Key::BACKSLASH;
				break;
			case SDLK_RIGHTBRACKET:
				key = Key::RIGHT_BRACKET;
				break;
			case SDLK_CARET:
				break;
			case SDLK_UNDERSCORE:
				break;
			case SDLK_BACKQUOTE:
				break;
			case SDLK_a:
				key = Key::A;
				break;
			case SDLK_b:
				key = Key::B;
				break;
			case SDLK_c:
				key = Key::C;
				break;
			case SDLK_d:
				key = Key::D;
				break;
			case SDLK_e:
				key = Key::E;
				break;
			case SDLK_f:
				key = Key::F;
				break;
			case SDLK_g:
				key = Key::G;
				break;
			case SDLK_h:
				key = Key::H;
				break;
			case SDLK_i:
				key = Key::I;
				break;
			case SDLK_j:
				key = Key::J;
				break;
			case SDLK_k:
				key = Key::K;
				break;
			case SDLK_l:
				key = Key::L;
				break;
			case SDLK_m:
				key = Key::M;
				break;
			case SDLK_n:
				key = Key::N;
				break;
			case SDLK_o:
				key = Key::O;
				break;
			case SDLK_p:
				key = Key::P;
				break;
			case SDLK_q:
				key = Key::Q;
				break;
			case SDLK_r:
				key = Key::R;
				break;
			case SDLK_s:
				key = Key::S;
				break;
			case SDLK_t:
				key = Key::T;
				break;
			case SDLK_u:
				key = Key::U;
				break;
			case SDLK_v:
				key = Key::V;
				break;
			case SDLK_w:
				key = Key::W;
				break;
			case SDLK_x:
				key = Key::X;
				break;
			case SDLK_y:
				key = Key::Y;
				break;
			case SDLK_z:
				key = Key::Z;
				break;
			case SDLK_CAPSLOCK:
				key = Key::CAPS_LOCK;
				break;
			case SDLK_F1:
				key = Key::F1;
				break;
			case SDLK_F2:
				key = Key::F1;
				break;
			case SDLK_F3:
				key = Key::F1;
				break;
			case SDLK_F4:
				key = Key::F1;
				break;
			case SDLK_F5:
				key = Key::F1;
				break;
			case SDLK_F6:
				key = Key::F1;
				break;
			case SDLK_F7:
				key = Key::F1;
				break;
			case SDLK_F8:
				key = Key::F1;
				break;
			case SDLK_F9:
				key = Key::F1;
				break;
			case SDLK_F10:
				key = Key::F1;
				break;
			case SDLK_F11:
				key = Key::F1;
				break;
			case SDLK_F12:
				key = Key::F1;
				break;
			case SDLK_PRINTSCREEN:
				break;
			case SDLK_SCROLLLOCK:
				break;
			case SDLK_PAUSE:
				break;
			case SDLK_INSERT:
				break;
			case SDLK_HOME:
				break;
			case SDLK_PAGEUP:
				break;
			case SDLK_DELETE:
				break;
			case SDLK_END:
				break;
			case SDLK_PAGEDOWN:
				break;
			case SDLK_RIGHT:
				break;
			case SDLK_LEFT:
				break;
			case SDLK_DOWN:
				break;
			case SDLK_UP:
				break;
			case SDLK_NUMLOCKCLEAR:
				break;
			case SDLK_KP_DIVIDE:
				break;
			case SDLK_KP_MULTIPLY:
				break;
			case SDLK_KP_MINUS:
				break;
			case SDLK_KP_PLUS:
				break;
			case SDLK_KP_ENTER:
				break;
			case SDLK_KP_1:
				break;
			case SDLK_KP_2:
				break;
			case SDLK_KP_3:
				break;
			case SDLK_KP_4:
				break;
			case SDLK_KP_5:
				break;
			case SDLK_KP_6:
				break;
			case SDLK_KP_7:
				break;
			case SDLK_KP_8:
				break;
			case SDLK_KP_9:
				break;
			case SDLK_KP_0:
				break;
			case SDLK_KP_PERIOD:
				break;
			case SDLK_APPLICATION:
				break;
			case SDLK_POWER:
				break;
			case SDLK_KP_EQUALS:
				break;
			case SDLK_F13:
				break;
			case SDLK_F14:
				break;
			case SDLK_F15:
				break;
			case SDLK_F16:
				break;
			case SDLK_F17:
				break;
			case SDLK_F18:
				break;
			case SDLK_F19:
				break;
			case SDLK_F20:
				break;
			case SDLK_F21:
				break;
			case SDLK_F22:
				break;
			case SDLK_F23:
				break;
			case SDLK_F24:
				break;
			case SDLK_EXECUTE:
				break;
			case SDLK_HELP:
				break;
			case SDLK_MENU:
				break;
			case SDLK_SELECT:
				break;
			case SDLK_STOP:
				break;
			case SDLK_AGAIN:
				break;
			case SDLK_UNDO:
				break;
			case SDLK_CUT:
				break;
			case SDLK_COPY:
				break;
			case SDLK_PASTE:
				break;
			case SDLK_FIND:
				break;
			case SDLK_MUTE:
				break;
			case SDLK_VOLUMEUP:
				break;
			case SDLK_VOLUMEDOWN:
				break;
			case SDLK_KP_COMMA:
				break;
			case SDLK_KP_EQUALSAS400:
				break;
			case SDLK_ALTERASE:
				break;
			case SDLK_SYSREQ:
				break;
			case SDLK_CANCEL:
				break;
			case SDLK_CLEAR:
				break;
			case SDLK_PRIOR:
				break;
			case SDLK_RETURN2:
				break;
			case SDLK_SEPARATOR:
				break;
			case SDLK_OUT:
				break;
			case SDLK_OPER:
				break;
			case SDLK_CLEARAGAIN:
				break;
			case SDLK_CRSEL:
				break;
			case SDLK_EXSEL:
				break;
			case SDLK_KP_00:
				break;
			case SDLK_KP_000:
				break;
			case SDLK_THOUSANDSSEPARATOR:
				break;
			case SDLK_DECIMALSEPARATOR:
				break;
			case SDLK_CURRENCYUNIT:
				break;
			case SDLK_CURRENCYSUBUNIT:
				break;
			case SDLK_KP_LEFTPAREN:
				break;
			case SDLK_KP_RIGHTPAREN:
				break;
			case SDLK_KP_LEFTBRACE:
				break;
			case SDLK_KP_RIGHTBRACE:
				break;
			case SDLK_KP_TAB:
				break;
			case SDLK_KP_BACKSPACE:
				break;
			case SDLK_KP_A:
				break;
			case SDLK_KP_B:
				break;
			case SDLK_KP_C:
				break;
			case SDLK_KP_D:
				break;
			case SDLK_KP_E:
				break;
			case SDLK_KP_F:
				break;
			case SDLK_KP_XOR:
				break;
			case SDLK_KP_POWER:
				break;
			case SDLK_KP_PERCENT:
				break;
			case SDLK_KP_LESS:
				break;
			case SDLK_KP_GREATER:
				break;
			case SDLK_KP_AMPERSAND:
				break;
			case SDLK_KP_DBLAMPERSAND:
				break;
			case SDLK_KP_VERTICALBAR:
				break;
			case SDLK_KP_DBLVERTICALBAR:
				break;
			case SDLK_KP_COLON:
				break;
			case SDLK_KP_HASH:
				break;
			case SDLK_KP_SPACE:
				break;
			case SDLK_KP_AT:
				break;
			case SDLK_KP_EXCLAM:
				break;
			case SDLK_KP_MEMSTORE:
				break;
			case SDLK_KP_MEMRECALL:
				break;
			case SDLK_KP_MEMCLEAR:
				break;
			case SDLK_KP_MEMADD:
				break;
			case SDLK_KP_MEMSUBTRACT:
				break;
			case SDLK_KP_MEMMULTIPLY:
				break;
			case SDLK_KP_MEMDIVIDE:
				break;
			case SDLK_KP_PLUSMINUS:
				break;
			case SDLK_KP_CLEAR:
				break;
			case SDLK_KP_CLEARENTRY:
				break;
			case SDLK_KP_BINARY:
				break;
			case SDLK_KP_OCTAL:
				break;
			case SDLK_KP_DECIMAL:
				break;
			case SDLK_KP_HEXADECIMAL:
				break;
			case SDLK_LCTRL:
				key = Key::LEFT_CONTROL;
				break;
			case SDLK_LSHIFT:
				key = Key::LEFT_SHIFT;
				break;
			case SDLK_LALT:
				key = Key::LEFT_ALT;
				break;
			case SDLK_LGUI:
				key = Key::LEFT_SUPER;
				break;
			case SDLK_RCTRL:
				key = Key::RIGHT_CONTROL;
				break;
			case SDLK_RSHIFT:
				key = Key::RIGHT_SHIFT;
				break;
			case SDLK_RALT:
				key = Key::RIGHT_ALT;
				break;
			case SDLK_RGUI:
				key = Key::RIGHT_SUPER;
				break;
			case SDLK_MODE:
				break;
			case SDLK_AUDIONEXT:
				break;
			case SDLK_AUDIOPREV:
				break;
			case SDLK_AUDIOSTOP:
				break;
			case SDLK_AUDIOPLAY:
				break;
			case SDLK_AUDIOMUTE:
				break;
			case SDLK_MEDIASELECT:
				break;
			case SDLK_WWW:
				break;
			case SDLK_MAIL:
				break;
			case SDLK_CALCULATOR:
				break;
			case SDLK_COMPUTER:
				break;
			case SDLK_AC_SEARCH:
				break;
			case SDLK_AC_HOME:
				break;
			case SDLK_AC_BACK:
				break;
			case SDLK_AC_FORWARD:
				break;
			case SDLK_AC_STOP:
				break;
			case SDLK_AC_REFRESH:
				break;
			case SDLK_AC_BOOKMARKS:
				break;
			case SDLK_BRIGHTNESSDOWN:
				break;
			case SDLK_BRIGHTNESSUP:
				break;
			case SDLK_DISPLAYSWITCH:
				break;
			case SDLK_KBDILLUMTOGGLE:
				break;
			case SDLK_KBDILLUMDOWN:
				break;
			case SDLK_KBDILLUMUP:
				break;
			case SDLK_EJECT:
				break;
			case SDLK_SLEEP:
				break;
			case SDLK_APP1:
				break;
			case SDLK_APP2:
				break;
			case SDLK_AUDIOREWIND:
				break;
			case SDLK_AUDIOFASTFORWARD:
				break;
			case SDLK_SOFTLEFT:
				break;
			case SDLK_SOFTRIGHT:
				break;
			case SDLK_CALL:
				break;
			case SDLK_ENDCALL:
				break;
		}
		mEventBus->Dispatch<KeyEvent>(key, keyState);
	}

#if defined(CGFX_APPLE)
	std::string Game::GetResource(const std::string& file, const std::string& type) {
		auto cfFile =
				CFStringCreateWithCString(nullptr, file.c_str(),
										  CFStringBuiltInEncodings::kCFStringEncodingUTF8);
		auto cfType =
				CFStringCreateWithCString(nullptr, type.c_str(),
										  CFStringBuiltInEncodings::kCFStringEncodingUTF8);
		auto appUrlRef =
				CFBundleCopyResourceURL(CFBundleGetMainBundle(), cfFile, cfType, NULL);

		auto macPath = CFURLCopyFileSystemPath(appUrlRef, kCFURLPOSIXPathStyle);
		auto resourcePathPtr(CFStringGetCStringPtr(macPath, CFStringGetSystemEncoding()));
		std::string resourcePath(resourcePathPtr);

		CFRelease(appUrlRef);
		CFRelease(macPath);
		CFRelease(cfType);
		CFRelease(cfFile);

		return resourcePath;
	};
#elif defined(CGFX_WINDOWS)

	std::string Game::GetResource(const std::string& file, const std::string& type) {
		return "./assets/" + file + "." + type;
	}
#endif

} // cgfx