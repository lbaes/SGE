#include <limits>
#include "CameraSystem.hpp"
#include "CGFX/ECS/Components/CameraTracker.hpp"
#include "CGFX/ECS/Components/TransformComponent.hpp"
#include "CGFX/Game/Game.hpp"

namespace cgfx {
	CameraSystem::CameraSystem(Camera2D& camera, Rect2D map) : camera(camera), mMap(map) {
		Require<CameraTracker, TransformComponent>();
	}

	void CameraSystem::UpdateFixed() {
		ForEach<TransformComponent>([this](const auto& transform) {
		  if (transform.position.x + ((double)camera.width / 2.0f) < mMap.width) {
			  int new_pos = static_cast<int>((transform.position.x - (static_cast<f32>(mMap.position_x) / 2.0f)));
			  camera.position_x = new_pos < 0 ? 0 : new_pos;
		  }

		  if (transform.position.y + ((double)camera.height / 2.0f) < mMap.height) {
			  int new_pos = static_cast<int>((transform.position.y - (static_cast<f32>(mMap.position_y) / 2.0f)));
			  camera.position_y = new_pos < 0 ? 0 : new_pos;
		  }

		  camera.position_x = camera.position_x > mMap.width  ? mMap.width : camera.position_x;
		  camera.position_y = camera.position_y > mMap.height ? mMap.width : camera.position_y;

		});
	}

	void CameraSystem::SetMapBoundaries(Rect2D map) {
		mMap = map;
	}

} // cgfx