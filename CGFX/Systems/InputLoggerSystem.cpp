#include "InputLoggerSystem.hpp"
#include <memory>

namespace cgfx {
	InputLoggerSystem::InputLoggerSystem(std::shared_ptr<EventBus> bus, std::shared_ptr<Logger> logger)
			: mEventBus(std::move(bus)), mLogger(std::move(logger)) {

		mEventBus->Subscribe<KeyEvent>([this](KeyEvent& event) {
		  OnKeyEvent(event);
		});

		mLogger->Info("InputLoggerSystem Initialized");
	}

	void InputLoggerSystem::Update() {
		for (const auto& message: mMessagesQueue) {
			mLogger->Info(message);
		}
		mMessagesQueue.clear();
	}

	void InputLoggerSystem::OnKeyEvent(KeyEvent& event) {
		std::string message;

		switch (event.state) {
			case KeyState::RELEASED:
				message = "Key Released {}, {}";
				break;
			case KeyState::PRESSED:
				message = "Key Press {}, {}";
				break;
			case KeyState::REPEAT:
				message = "Key Repeat {}, {}";
				break;
		}
		mLogger->Info(message, KeyToInt(event.key), ModifierToInt(event.modifiers[0]));
	}
} // cgfx