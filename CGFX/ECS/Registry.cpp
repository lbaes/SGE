
#include "Registry.hpp"
#include "System.hpp"

namespace cgfx {

    Registry::Registry() : mAvailableEntities(MAX_ENTITIES), mAliveEntities(0) {
        mEntityComponentSignatures.resize(MAX_ENTITIES);
        std::iota(mAvailableEntities.begin(), mAvailableEntities.end(), 0);
        std::fill(mEntityComponentSignatures.begin(), mEntityComponentSignatures.end(),
                  std::bitset<MAX_COMPONENTS_PER_ENTITY>());
    }

    Entity Registry::CreateEntity() {
        if (mAliveEntities < MAX_ENTITIES) {
            auto newEntity = mAvailableEntities.front();
            mAvailableEntities.pop_front();
            mUpdateQueue.emplace(newEntity);
            ++mAliveEntities;
            return newEntity;
        }
        throw MaximumNumberOfAliveEntitiesExceededException(MAX_ENTITIES);
    }

    void Registry::DeleteEntity(Entity entity) {

		if (mUpdateQueue.contains(entity)){
			mUpdateQueue.erase(entity);
			return;
		}

        if (entity <= MAX_ENTITIES && !cstd::contains(mAvailableEntities, entity)) {
            mDeletionQueue.emplace(entity);
			return;
        }
        throw DeleteUncreatedEntityException();
    }

    size_t Registry::GetNumberOfLiveEntities() const {
        return mAliveEntities;
    }

    void Registry::Update() {
        for (auto entity: mDeletionQueue) {
            mEntityComponentSignatures[entity].reset();
            mAvailableEntities.push_back(entity);
            UpdateEntitiesOnSystems(entity);
        }

        for (auto entity: mUpdateQueue) {
            UpdateEntitiesOnSystems(entity);
        }

        mDeletionQueue.clear();
        mUpdateQueue.clear();
    }

    void Registry::UpdateEntitiesOnSystems(Entity entity) {
        for (auto& pair: mSystems) {
            const auto& entitySignature = mEntityComponentSignatures.at(entity);
            const auto& system = pair.second;
            const auto& systemSignature = system->GetComponentSignature();

            // if signatures match add entity to system, else remove entity from system
            if ((entitySignature & systemSignature) == systemSignature) {
                system->AddEntity(entity);
            } else {
                system->RemoveEntity(entity);
            }
        }
    }

    void Registry::ClearComponent(Entity entity) {
        mEntityComponentSignatures.at(entity) &= 0;
    }
}
