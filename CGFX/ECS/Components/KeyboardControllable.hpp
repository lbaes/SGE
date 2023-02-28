#ifndef CGFX_KEYBOARDCONTROLLABLE_HPP
#define CGFX_KEYBOARDCONTROLLABLE_HPP

#include "glm/glm.hpp"

namespace cgfx {

	struct KeyboardControllable {
		glm::vec2 up;
		glm::vec2 right;
		glm::vec2 down;
		glm::vec2 left;

		KeyboardControllable(glm::vec2 up, glm::vec2 right, glm::vec2 down, glm::vec2 left)
				: up(up), right(right), down(down), left(left) {
		}

	};

} // cgfx

#endif //CGFX_KEYBOARDCONTROLLABLE_HPP
