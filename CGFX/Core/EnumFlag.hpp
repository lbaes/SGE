#ifndef CGFX_ENUMFLAG_HPP
#define CGFX_ENUMFLAG_HPP

#include <type_traits>

namespace cgfx {

    template<class T> concept valid_enum_flag =
    std::is_enum_v<T> &&
    std::is_unsigned_v<std::underlying_type_t<T>>;

    template<class T>
    requires valid_enum_flag<T> inline T operator~(T a) { return (T) ~(int) a; }

    template<class T>
    requires valid_enum_flag<T> inline T operator|(T a, T b) { return (T) ((int) a | (int) b); }

    template<class T>
    requires valid_enum_flag<T> inline T operator&(T a, T b) { return (T) ((int) a & (int) b); }

    template<class T>
    requires valid_enum_flag<T> inline T operator^(T a, T b) { return (T) ((int) a ^ (int) b); }

    template<class T>
    requires valid_enum_flag<T> inline T& operator|=(T& a, T b) { return (T&) ((int&) a |= (int) b); }

    template<class T>
    requires valid_enum_flag<T> inline T& operator&=(T& a, T b) { return (T&) ((int&) a &= (int) b); }

    template<class T>
    requires valid_enum_flag<T> inline T& operator^=(T& a, T b) { return (T&) ((int&) a ^= (int) b); }
}


#endif //CGFX_ENUMFLAG_HPP
