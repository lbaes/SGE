#ifndef CGFX_ASSERTIONS_HPP
#define CGFX_ASSERTIONS_HPP

#include <csignal>
#include "Logger.hpp"

#if CGFX_ASSERTIONS_ENABLED

#define debugBreak() { std::raise(SIGTRAP) }

#define CGFX_ASSERT(expr) \
    if (expr) {}          \
    else {                \
    logger->Critical("{}, file: {}, line: {}", #expr, __FILE__, __LINE__); \
    debugBreak();\
    }

#else
#define CGFX_ASSERT(expr)
#endif

#endif //CGFX_ASSERTIONS_HPP
