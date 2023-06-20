#ifndef CGFX_PLATFORM_HPP
#define CGFX_PLATFORM_HPP
#include <cstdint>
#include <vector>
#include <array>
#include <string>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat2x2.hpp>
#include <glm/mat3x3.hpp>
#include <glm/mat4x4.hpp>

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

	using String = std::string;
	template <typename T>
	using Vector = std::vector<T>;

	template<typename T, auto N>
	using Array  = std::array<T, N>;


}

#endif //CGFX_PLATFORM_HPP
