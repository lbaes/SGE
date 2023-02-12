#ifndef CGFX_COLLISIONEVENT_HPP
#define CGFX_COLLISIONEVENT_HPP

#include "CGFX/Event/EventBus.hpp"
#include "CGFX/ECS/Entity.hpp"

namespace cgfx {

	struct CollisionEvent : public EventBase {
		CollisionEvent(Entity a, Entity b) : a(a), b(b){

		}
		Entity a;
		Entity b;
	};

} // cgfx

#endif //CGFX_COLLISIONEVENT_HPP
