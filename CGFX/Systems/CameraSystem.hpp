#ifndef CGFX_CAMERASYSTEM_HPP
#define CGFX_CAMERASYSTEM_HPP

#include "CGFX/ECS/System.hpp"
#include "CGFX/Core/Camera2D.hpp"

namespace cgfx {

	class CameraSystem : public System {
	public:
		explicit CameraSystem(Camera2D& camera, Rect2D map);
		void SetMapBoundaries(Rect2D map);
		void UpdateFixed();
	private:
		Camera2D& camera;
		Rect2D mMap;
	};

} // cgfx

#endif //CGFX_CAMERASYSTEM_HPP
