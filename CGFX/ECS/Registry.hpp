#ifndef CGFX_REGISTRY_HPP
#define CGFX_REGISTRY_HPP

#include "CGFX/Core/Core.hpp"

#include "Entity.hpp"
#include "Component.hpp"
#include "Exception.hpp"
#include "CGFX/Core/Macros.hpp"
#include "CGFX/Core/Reflection.hpp"
#include "CGFX/Core/AlgorithmExtension.hpp"
#include "CGFX/Core/Logger.hpp"

using namespace std::literals::string_literals;

namespace cgfx {

    class System;

    class Registry {
    public:

        Registry();

        ~Registry() = default;

        DELETE_COPY_AND_ASSIGN(Registry);
        DEFAULT_MOVE_AND_ASSIGN(Registry);

        // Entities

        [[nodiscard]]
        Entity CreateEntity();

        void DeleteEntity(Entity entity);

        size_t GetNumberOfLiveEntities() const;

        // Component //

        template<typename ComponentT, typename... Args>
        void AddComponent(Entity entity, Args&& ... args) {

            auto componentId = Component<ComponentT>::GetId();
            if (componentId >= mComponentPools.size()) {
                mComponentPools.resize((componentId + 1) * 2);
            }

            // allocate component pool for components of type ComponentT if it doesn't exist yet
            auto& componentPool = mComponentPools.at(componentId);
            if (componentPool == nullptr) {
                componentPool = std::move(std::make_shared<Pool<ComponentT>>());
            }

            // increase pool size if necessary
            auto pool = GetTypedPool<ComponentT>();
            if (entity >= pool->GetSize()) {
                if constexpr (std::is_aggregate_v<ComponentT>) {
                    pool->Resize(mAliveEntities, ComponentT{std::forward<Args>(args)...});
                } else {
                    pool->Resize(mAliveEntities, ComponentT(std::forward<Args>(args)...));
                }
            }

            if constexpr (std::is_aggregate_v<ComponentT>) {
                pool->Set(entity, ComponentT{std::forward<Args>(args)...});
            } else {
                pool->Set(entity, ComponentT(std::forward<Args>(args)...));
            }
            mEntityComponentSignatures.at(entity).set(componentId);
            mUpdateQueue.emplace(entity);
        }

        template<typename ComponentT>
        void RemoveComponent(Entity entity) {
            auto componentId = Component<ComponentT>::GetId();
            mEntityComponentSignatures.at(entity).set(componentId, false);
			mUpdateQueue.emplace(entity);
        }

        template<typename T>
        bool HasComponent(Entity entity) const {
            auto componentId = Component<T>::GetId();
            return mEntityComponentSignatures.at(entity).test(componentId);
        }

        template<typename ComponentT>
        ComponentT& GetComponent(Entity entity) {
            return (*GetTypedPool<ComponentT>())[entity];
        }

        void ClearComponent(Entity entity);

        // SYSTEMS //

        template<typename SystemT, typename ...Args>
        void RegisterSystem(Args&& ...args) {
			auto system = std::make_shared<SystemT>(std::forward<Args>(args)...);
			system->SetRegistry(this);
            mSystems.insert({typeid(SystemT), std::move(system)});
        }

        template<typename SystemT>
        SystemT& GetSystem() const {
            auto system = mSystems.at(typeid(SystemT));
			assert(system != nullptr && "system was used before being registered!");
            return *std::static_pointer_cast<SystemT>(system);
        }

        template<typename SystemT>
        void RemoveSystem() {
            mSystems.erase(typeid(SystemT));
        }

        void Update();

    private:
        void UpdateEntitiesOnSystems(Entity entity);

        template<typename ComponentT>
        std::shared_ptr<Pool<ComponentT>> GetTypedPool() {
            auto componentId = Component<ComponentT>::GetId();
            assert(componentId < mComponentPools.size() && "out of range access on component pool ptr vector");
            return std::static_pointer_cast<Pool<ComponentT>>(mComponentPools.at(componentId));
        }

        std::vector<std::shared_ptr<IPool>> mComponentPools;
        std::vector<Signature> mEntityComponentSignatures;
        std::unordered_map<std::type_index, std::shared_ptr<System>> mSystems;
        std::deque<Entity> mAvailableEntities;
        std::set<Entity> mDeletionQueue;
        std::set<Entity> mUpdateQueue;
        std::uint32_t mAliveEntities;
    };

} // cgfx

#endif //CGFX_REGISTRY_HPP
