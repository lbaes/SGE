#ifndef CGFX_SYSTEM_HPP
#define CGFX_SYSTEM_HPP

#include "CGFX/ECS/Registry.hpp"
#include "CGFX/Core/AlgorithmExtension.hpp"

namespace cgfx {

    class System {
    public:

        using iterator = typename std::vector<Entity>::iterator;

        void AddEntity(Entity entity) {
            mEntities.emplace_back(entity);
        }

        void RemoveEntity(Entity entity) {
            cstd::remove(mEntities, entity);
        }

        const std::vector<Entity>& GetEntities() const {
            return mEntities;
        }

        iterator begin()  {
            return mEntities.begin();
        }

        iterator end()  {
            return mEntities.end();
        }

        size_t GetNumberOfEntitiesOnSystem() const noexcept {
            return mEntities.size();
        }

        void SetRegistry(Registry *registry) noexcept {
            assert(registry != nullptr && "registry can't be null");
            mRegistry = registry;
        }

        template<typename ComponentT>
        ComponentT& GetComponent(Entity entity) const {
            return mRegistry->GetComponent<ComponentT>(entity);
        }

        template<typename ComponentT>
        bool HasComponent(Entity entity) {
            return mRegistry->HasComponent<ComponentT>(entity);
        }

        const Signature& GetComponentSignature() const {
            return mComponentSignature;
        }

        template<typename F>
        void SortEntities(F&& comp) {
            std::sort(mEntities.begin(), mEntities.end(), comp);
        }

        template<typename ...ComponentTs>
        void Require() {
            mComponentSignature
                    |= (Signature().set(Component<ComponentTs>::GetId())
                    |= ...);
        }

        template<typename ...ComponentTs, typename F>
        void ForEach(F&& f) requires std::invocable<F, ComponentTs& ...> || std::invocable<F, Entity, ComponentTs& ...> {
            ForEach<ComponentTs...>(mEntities.begin(), mEntities.end(), f);
        }

        template<typename ...ComponentTs, typename F>
        void ForEach(iterator begin, iterator end, F&& f) requires std::invocable<F, ComponentTs& ...> {
            for (auto it = begin; it != end; ++it) {
                f(mRegistry->GetComponent<ComponentTs>(*it)...);
            }
        }

        template<typename ...ComponentTs, typename F>
        void ForEach(iterator begin, iterator end, F&& f) requires std::invocable<F, Entity, ComponentTs& ...> {
            for (auto it = begin; it != end; ++it) {
                f(*it, mRegistry->GetComponent<ComponentTs>(*it)...);
            }
        }

    private:
        Registry *mRegistry = nullptr;
        Signature mComponentSignature;
        std::vector<Entity> mEntities;
    };
} // cgfx

#endif //CGFX_SYSTEM_HPP
