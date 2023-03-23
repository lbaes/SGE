#ifndef CGFX_CAMERATRACKER_HPP
#define CGFX_CAMERATRACKER_HPP

#include "CGFX/ECS/Component.hpp"
#include "CGFX/Core/Math.hpp"
#include "CGFX/Core/Reflection.hpp"

namespace cgfx {

	struct CameraTracker {
		bool isActive = false;
	};

	ENABLE_TYPENAME(CameraTracker)

} // cgfx

#endif //CGFX_CAMERATRACKER_HPP
