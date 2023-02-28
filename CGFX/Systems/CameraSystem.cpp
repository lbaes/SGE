#include "CameraSystem.hpp"
#include "CGFX/ECS/Components/CameraTracker.hpp"
#include "CGFX/ECS/Components/TransformComponent.hpp"

namespace cgfx {
	CameraSystem::CameraSystem() {
		Require<TransformComponent>();
	}

	void CameraSystem::UpdateFixed() {
		ForEach<CameraTracker, TransformComponent>([](auto& camera, auto& transform){
			if (!camera.isActive){
				return;
			}

		});
	}
} // cgfx