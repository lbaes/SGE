#include <limits>
#include "CameraSystem.hpp"
#include "CGFX/ECS/Components/CameraTracker.hpp"
#include "CGFX/ECS/Components/TransformComponent.hpp"

namespace cgfx {
	CameraSystem::CameraSystem(Camera2D& camera, Rect2D map) : camera(camera), mMap(map) {
		Require<CameraTracker, TransformComponent>();
	}

	void CameraSystem::UpdateFixed() {
		ForEach<TransformComponent>([&](const auto& transform) {
		  if (transform.position.x + (camera.width / 2) < mMap.width) {
			  int new_pos = transform.position.x - (mMap.position_x / 2);
			  camera.position_x = new_pos < 0 ? 0 : new_pos;
		  }

		  if (transform.position.y + (camera.height / 2) < mMap.height) {
			  int new_pos = transform.position.y - (mMap.position_y / 2);
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