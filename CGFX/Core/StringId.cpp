#include "detail/MurmurHash3.hpp"
#include "StringId.hpp"

cgfx::StringId cgfx::MakeStringId(const std::string& key) {
    u32 output = 0;
    MurmurHash3_x86_32(key.c_str(), static_cast<int>(key.length()), 0, &output);
    return output;
}
