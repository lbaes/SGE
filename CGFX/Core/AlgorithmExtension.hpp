#ifndef CGFX_ALGORITHMEXTENSION_HPP
#define CGFX_ALGORITHMEXTENSION_HPP

#include <vector>

namespace cgfx::cstd {
    template<typename T>
    inline void remove(std::vector<T>& v, const T& item) {
        v.erase(std::remove(v.begin(), v.end(), item), v.end());
    }

    template<typename T, typename Predicate>
    inline void remove_if(std::vector<T>& v, Predicate predicate) {
        v.erase(std::remove_if(v.begin(), v.end(), predicate), v.end());
    }

    template<typename Container, typename value_type>
    inline bool contains(const Container& container, const value_type& value) {
        return std::find(container.begin(), container.end(), value) != container.end();
    }
}


#endif //CGFX_ALGORITHMEXTENSION_HPP
