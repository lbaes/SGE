#ifndef CGFX_INPUTLOGGERSYSTEM_HPP
#define CGFX_INPUTLOGGERSYSTEM_HPP

#include <string>
#include <vector>
#include <memory>
#include "CGFX/ECS/System.hpp"
#include "CGFX/Event/Events/InputEvents.hpp"

namespace cgfx {

	class InputLoggerSystem : public System {
	public:
		explicit InputLoggerSystem(std::shared_ptr<EventBus> bus, std::shared_ptr<Logger> logger);
		void Update();
		void OnKeyEvent(KeyEvent& keyEvent);

	private:
		std::shared_ptr<EventBus> mEventBus;
		std::shared_ptr<Logger> mLogger;
		std::vector<std::string> mMessagesQueue;
	};

} // cgfx

#endif //CGFX_INPUTLOGGERSYSTEM_HPP
