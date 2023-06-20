#ifndef CGFX_COMPONENT_HPP
#define CGFX_COMPONENT_HPP

#include "CGFX/Core/Core.hpp"
#include "CGFX/Core/Macros.hpp"
#include "CGFX/Core/Assertions.hpp"

namespace cgfx {

    const u32 MAX_COMPONENTS_PER_ENTITY = 32;
    using Signature = std::bitset<MAX_COMPONENTS_PER_ENTITY>;

    class IComponent {
    public:
        IComponent() = delete;
    protected:
        static u64 mId; // NOLINT(cppcoreguidelines-avoid-non-const-global-variables)
    };

    inline u64 IComponent::mId = 0; // NOLINT(cppcoreguidelines-avoid-non-const-global-variables)

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

		Pool() = default;
		Pool(u64 initial_capacity) {
			mPool.reserve(initial_capacity);
		}

        void Set(u64 index, const ComponentT& item) {
            mPool.at(index) = item;
        }

		u64 GetCapacity() const noexcept {
            return mPool.capacity();
        }

		u64 GetSize() const noexcept {
            return mPool.size();
        }

		void Reserve(u64 count){
			mPool.reserve(count);
		}

        void Resize(u64 count) {
            mPool.resize(count);
        }

        template<typename ...Args>
        void Resize(u64 count, Args&& ... args) {
            mPool.resize(count, std::forward<Args>(args)...);
        }

        ComponentT& operator[](u64 index) {
            CGFX_ASSERT(index < mPool.size() && "index out of range");
            return mPool[index];
        }

        const ComponentT& operator[](u64 index) const {
			CGFX_ASSERT(index < mPool.size() && "index out of range");
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
