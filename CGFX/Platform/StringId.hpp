#ifndef CGFX_STRINGID_HPP
#define CGFX_STRINGID_HPP

#include "Platform.hpp"

namespace cgfx {

    using StringId = u32;
    StringId MakeStringId(const std::string&);

    inline static StringId operator "" _id(const char *name, size_t) {
        return MakeStringId(name);
    }

}

#endif //CGFX_STRINGID_HPP
