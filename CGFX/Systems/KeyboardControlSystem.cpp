#include "KeyboardControlSystem.hpp"
#include "CGFX/ECS/Components/KeyboardControllable.hpp"
#include "CGFX/ECS/Components/RigidBodyComponent.hpp"
#include "CGFX/Event/Events/InputEvents.hpp"

namespace cgfx {
	KeyboardControlSystem::KeyboardControlSystem(std::shared_ptr<EventBus> bus) : mEventBus(std::move(bus)) {
		Require<KeyboardControllable, RigidBodyComponent>();
		mEventBus->Subscribe<KeyEvent>([this](KeyEvent& event) {
		  OnKeyPress(event);
		});
	}

	void KeyboardControlSystem::UpdateFixed() {

	}

	void KeyboardControlSystem::OnKeyPress(KeyEvent& keyEvent) {
		ForEach<KeyboardControllable, RigidBodyComponent>([&](auto& k, auto& r) {
		  if (keyEvent.state == KeyState::PRESSED) {
			  switch (keyEvent.key) {
				  case Key::W:
					  r.velocity += -k.up;
					  break;
				  case Key::A:
					  r.velocity += -k.left;
					  break;
				  case Key::S:
					  r.velocity += k.down;
					  break;
				  case Key::D:
					  r.velocity += k.right;
					  break;
				  default:
					  break;
			  }
		  } else if (keyEvent.state == KeyState::RELEASED) {
			  switch (keyEvent.key) {
				  case Key::W:
					  r.velocity -= -k.up;
					  break;
				  case Key::A:
					  r.velocity -= -k.left;
					  break;
				  case Key::S:
					  r.velocity -= k.down;
					  break;
				  case Key::D:
					  r.velocity -= k.right;
					  break;
				  default:
					  break;
			  }
		  }
		});

	}


} // cgfx