#ifndef CGFX_CORE_HPP
#define CGFX_CORE_HPP

#include <cstdint>
#include <vector>
#include <bitset>
#include <cassert>
#include <unordered_map>
#include <string>
#include <stdexcept>
#include <sstream>
#include <set>
#include <queue>
#include <typeindex>
#include <numeric>
#include <any>
#include <iostream>
#include <utility>
#include <set>
#include <typeindex>
#include <functional>
#include <memory>
#include <glm/glm.hpp>
#include <gsl/pointers>


namespace cgfx {
	using f32 = float;
	using f64 = long;

	using u8 = std::uint8_t;
	using u16 = std::uint16_t;
	using u32 = std::uint32_t;
	using u64 = std::uint64_t;

	using i8 = std::int8_t;
	using i16 = std::int16_t;
	using i32 = std::int32_t;
	using i64 = std::int64_t;

	using vec2 = glm::vec2;
	using vec3 = glm::vec3;

	using vec2i = glm::vec<2, i32>;
	using vec3i = glm::vec<3, i32>;

	using string = std::string;
	using std::vector;
}

#endif //CGFX_CORE_HPP
