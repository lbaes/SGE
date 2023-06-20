#ifndef CGFX_LOGGER_HPP
#define CGFX_LOGGER_HPP

#include "CGFX/Core/Core.hpp"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"

namespace cgfx {

    class Logger {
	public:

		explicit Logger(const std::string& name) {
            try {
                mConsoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
				mLogger = std::make_unique<spdlog::logger>(name, mConsoleSink);
            } catch (const spdlog::spdlog_ex& ex) {
                handle_exception(ex);
                throw;
            }
        }

        Logger(const std::string& name, const std::string& file_path) {
            try {
                mFileSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(file_path);
                mConsoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
                mLogger = std::make_unique<spdlog::logger>(name, mFileSink);
            } catch (const spdlog::spdlog_ex& ex) {
                handle_exception(ex);
                throw;
            }
        }

        template<typename... Ts>
		void Info(const std::string& message, Ts&& ... args) {
            mLogger->info(fmt::runtime(message), std::forward<Ts>(args)...);
        };

        template<typename... Ts>
        void Warn(const std::string& message, Ts&& ... args) {
            mLogger->warn(fmt::runtime(message), std::forward<Ts>(args)...);
        };

        template<typename... Ts>
        void Error(const std::string& message, Ts&& ... args) {
            mLogger->error(fmt::runtime(message), std::forward<Ts>(args)...);
        };

        template<typename... Ts>
        void Critical(const std::string& message, Ts&& ... args) {
            mLogger->critical(fmt::runtime(message), std::forward<Ts>(args)...);
        };

    private:
        std::unique_ptr<spdlog::logger> mLogger;
        std::shared_ptr<spdlog::sinks::basic_file_sink_mt> mFileSink;
        std::shared_ptr<spdlog::sinks::stdout_color_sink_mt> mConsoleSink;

        static void handle_exception(const spdlog::spdlog_ex& ex) {
            std::cerr << "Logger initialization failed" << ex.what() << std::endl;
        }
    };

#ifdef CGFX_DEBUG
	inline static Logger* DebugLogger;

	inline void InitDebugLogger() {
		if (!DebugLogger){
			DebugLogger = new Logger("ENGINE");
		}
	}

	inline void ShutdownDebugLogger() {
		if (DebugLogger){
			delete DebugLogger;
		}
	}

	template<typename... Ts>
	void LogDebugInfo(const char* msg, Ts&& ... args){
		if (DebugLogger)
			DebugLogger->Info(msg, std::forward<Ts>(args)...);
	}

	template<typename... Ts>
	void LogDebugError(const char* msg, Ts&& ... args){
		if (DebugLogger)
			DebugLogger->Error(msg, std::forward<Ts>(args)...);
	}

#define CGFX_DEBUG_LOG(...) cgfx::LogDebugInfo(__VA_ARGS__)

#else
#define CGFX_DEBUG_LOG(...)
#endif
} // cgfx

#endif //CGFX_LOGGER_HPP
