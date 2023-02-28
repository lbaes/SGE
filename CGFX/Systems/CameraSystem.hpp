#ifndef CGFX_CAMERASYSTEM_HPP
#define CGFX_CAMERASYSTEM_HPP

#include "CGFX/ECS/System.hpp"

namespace cgfx {

	class CameraSystem : public System {
	public:
		CameraSystem();
		void UpdateFixed();
	};

} // cgfx

#endif //CGFX_CAMERASYSTEM_HPP
