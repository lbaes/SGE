#ifndef CGFX_KEYBOARDCONTROLSYSTEM_HPP
#define CGFX_KEYBOARDCONTROLSYSTEM_HPP

#include "CGFX/ECS/System.hpp"
#include "CGFX/Event/Events/InputEvents.hpp"

namespace cgfx {

	class KeyboardControlSystem : public System {
	public:
		explicit KeyboardControlSystem(std::shared_ptr<EventBus> bus);

		void UpdateFixed();

		void OnKeyPress(KeyEvent& keyEvent);
	private:
		std::shared_ptr<EventBus> mEventBus;
	};

} // cgfx

#endif //CGFX_KEYBOARDCONTROLSYSTEM_HPP
