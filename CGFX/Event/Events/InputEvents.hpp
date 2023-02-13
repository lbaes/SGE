#ifndef CGFX_INPUTEVENTS_HPP
#define CGFX_INPUTEVENTS_HPP

#include <array>
#include "CGFX/Core/Keys.hpp"
#include "CGFX/Event/EventBus.hpp"

namespace cgfx {

	struct KeyEvent : EventBase {
		explicit KeyEvent(Key key, KeyState state) : key(key), state(state) {

		}

		Key key = Key::UNKNOWN;
		KeyState state = KeyState::PRESSED;
		std::array<Modifiers, 4> modifiers{Modifiers::NONE};
	};

	struct MouseEvent : EventBase {
		MouseButton mouseButton = MouseButton::NONE;
		float x{}, y{};
	};


} // cgfx

#endif //CGFX_INPUTEVENTS_HPP
