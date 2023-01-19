#ifndef CGFX_REFLECTION_HPP
#define CGFX_REFLECTION_HPP

#include <typeinfo>

namespace cgfx {
    template<typename T>
    struct TypeName {
        static const char *Get() {
            return typeid(T).name();
        }
    };
} // cgfx

#define ENABLE_TYPENAME(A) template<> struct cgfx::TypeName<A> { static const char *Get() { return #A; }};

#endif //CGFX_REFLECTION_HPP
