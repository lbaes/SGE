#ifndef CGFX_LOGGER_HPP
#define CGFX_LOGGER_HPP

#include <string>
#include "spdlog/spdlog.h"

namespace cgfx {

    class Logger {
    public:
        template<typename... Ts>
        static void Info(const std::string& message, Ts&& ... args) {
            spdlog::info(message, std::forward<Ts>(args)...);
        };

        template<typename... Ts>
        static void Warn(const std::string& message, Ts&& ... args) {
            spdlog::warn(message, std::forward<Ts>(args)...);
        };

        template<typename... Ts>
        static void Error(const std::string& message, Ts&& ... args) {
            spdlog::error(message, std::forward<Ts>(args)...);
        };

        template<typename... Ts>
        static void Critical(const std::string& message, Ts&& ... args) {
            spdlog::critical(message, std::forward<Ts>(args)...);
        };
    };

} // cgfx

#endif //CGFX_LOGGER_HPP
