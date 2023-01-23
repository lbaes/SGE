#ifndef CGFX_ASSETSTORE_HPP
#define CGFX_ASSETSTORE_HPP

#include <string>
#include <memory>
#include <unordered_map>
#include "CGFX/Core/StringId.hpp"

namespace cgfx {

    template<typename AssetT>
    class AssetStore {
    public:
        using handle_type = std::shared_ptr<AssetT>;
        using key_type = StringId;
        using iterator = typename std::unordered_map<key_type, handle_type>::iterator;

        template<typename ...Args>
        std::pair<iterator, bool> Load(const key_type& key, Args&& ... args) {
            if (auto it = mAssetStoreMap.find(key); it != mAssetStoreMap.end()) {
                return {it, false};
            }
            return mAssetStoreMap.emplace(key, std::make_shared<AssetT>(std::forward<Args>(args)...));
        }

        template<typename ...Args>
        std::pair<iterator, bool> Reload(const key_type& key, Args&& ... args) {
            return mAssetStoreMap.insert_or_assign(key, std::make_shared<AssetT>(std::forward<Args>(args)...));
        }

        handle_type Get(const key_type& key) {
            return mAssetStoreMap.at(key);
        }

        bool Contains(const key_type& key) {
            return mAssetStoreMap.contains(key);
        }

    private:
        std::unordered_map<key_type, handle_type> mAssetStoreMap;
    };

} // cgfx

#endif //CGFX_ASSETSTORE_HPP
