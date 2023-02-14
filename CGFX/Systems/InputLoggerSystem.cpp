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

		int numeric_key_code = KeyToInt(event.key);
		if (numeric_key_code > 32  && numeric_key_code < 126){
			char ascii = static_cast<char>(numeric_key_code);
			mLogger->Info(message, ascii, ModifierToInt(event.modifiers[0]));
		}else {
			mLogger->Info(message, numeric_key_code, ModifierToInt(event.modifiers[0]));
		}

	}
} // cgfx