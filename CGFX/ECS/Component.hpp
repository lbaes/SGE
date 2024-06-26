#ifndef CGFX_COMPONENT_HPP
#define CGFX_COMPONENT_HPP

#include "CGFX/Core/Core.hpp"
#include "CGFX/Core/Macros.hpp"

namespace cgfx {

    const u32 MAX_COMPONENTS_PER_ENTITY = 32;
    using Signature = std::bitset<MAX_COMPONENTS_PER_ENTITY>;

    class IComponent {
    public:
        IComponent() = delete;
    protected:
        static u32 mId; // NOLINT(cppcoreguidelines-avoid-non-const-global-variables)
    };

    inline u32 IComponent::mId = 0; // NOLINT(cppcoreguidelines-avoid-non-const-global-variables)

    template<typename>
    class Component : public IComponent {
    public:
        static u32 GetId() {
            static auto id = mId++;
            return id;
        }
    };

    class IPool {
    INTERFACE(IPool)
    };

    template<typename ComponentT>
    class Pool : public IPool {
    public:
        using iterator = typename std::vector<ComponentT>::iterator;
        using const_iterator = typename std::vector<ComponentT>::const_iterator;

        void Add(const ComponentT& item) {
            mPool.push_back(item);
        }

        void Add(ComponentT&& item) {
            mPool.push_back(item);
        }

        void Set(size_t index, const ComponentT& item) {
            mPool.at(index) = item;
        }

        std::size_t GetCapacity() const noexcept {
            return mPool.capacity();
        }

        std::size_t GetSize() const noexcept {
            return mPool.size();
        }

        void Resize(i32 count) {
            mPool.resize(count);
        }

        template<typename ...Args>
        void Resize(i32 count, Args&& ... args) {
            mPool.resize(count, std::forward<Args>(args)...);
        }

        ComponentT& operator[](size_t index) {
            assert(index < mPool.size() && "index out of range");
            return mPool[index];
        }

        const ComponentT& operator[](size_t index) const {
            assert(index < mPool.size() && "index out of range");
            return mPool[index];
        }

        iterator begin() {
            return mPool.begin();
        }

        iterator end() {
            return mPool.end();
        }

        const_iterator begin() const {
            return mPool.begin();
        }

        const_iterator end() const {
            return mPool.end();
        }

    private:
        std::vector<ComponentT> mPool;
    };

} // cgfx

#endif //CGFX_COMPONENT_HPP
