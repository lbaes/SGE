#ifndef CGFX_EXCEPTION_HPP
#define CGFX_EXCEPTION_HPP

#include "CGFX/Core/Core.hpp"

namespace cgfx {

    class MaximumNumberOfAliveEntitiesExceededException : public std::runtime_error {
    public:
        explicit MaximumNumberOfAliveEntitiesExceededException(std::size_t maxEntities) : std::runtime_error("") {
            std::stringstream buf;
            buf << "Maximum number of allowed entities exceeded " << maxEntities;
            mMessage = buf.str();
        }

        const char *what() const noexcept override {
            return mMessage.c_str();
        }

    private:
        std::string mMessage;
    };

    class DeleteUncreatedEntityException : public std::runtime_error {
    public:
        explicit DeleteUncreatedEntityException() : std::runtime_error(
                "Attempted to delete an Entity that was not created or is invalid") {
        }
    };

    class SystemNotRegisteredException : public std::runtime_error {
    public:
        explicit SystemNotRegisteredException(const std::string& systemName) : std::runtime_error(systemName) {

        }
    };

} // cgfx

#endif //CGFX_EXCEPTION_HPP
