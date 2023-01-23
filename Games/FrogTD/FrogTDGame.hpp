#ifndef CGFX_FROGTDGAME_HPP
#define CGFX_FROGTDGAME_HPP

#include <fstream>
#include "CGFX/CGFX.hpp"
#include <corefoundation/CFBundle.h>

using namespace cgfx;

class FrogTDGame final : public Game {
public:
    void OnGameStart() override;
    void OnGameUpdate(float dt) override;
    void OnGameFixedUpdate() override;
private:
    void LoadMap(const std::string& file, const std::string& texFile, int tileScale);
    Entity ladybug;
    std::vector<Entity> frogs;
};

void FrogTDGame::LoadMap(const std::string& file, const std::string& texFile, int tileScale) {
    const int tile_size = 32;
    const int tile_map_cols = 3;
    const int tile_scale = tileScale;
    std::ifstream map_file(file);
    std::string line;
    int x = 0;
    int y = 0;
    while (std::getline(map_file, line)) {
        std::istringstream iss(line);
        std::string index_string;
        int count = 0;
        y = 0;
        while (std::getline(iss, index_string, ',')) {
            count++;
            int index = std::stoi(index_string);
            int index_x = index % tile_map_cols;
            int index_y = index / tile_map_cols;
            auto map_tile = GetRegistry().CreateEntity();
            GetRegistry().AddComponent<SpriteComponent>(map_tile, texFile,
                                                        Rect2D(index_x, index_y, 32, 32), 0);
            GetRegistry().AddComponent<TransformComponent>(map_tile, y, x, tile_scale, tile_scale);
            y += tile_size * tile_scale;
        }
        x += tile_size * tile_scale;
    }
}

void FrogTDGame::OnGameStart() {

    auto getResource = [](const std::string& file, const std::string& type){
        CFStringRef cfFile = CFStringCreateWithCString(NULL, file.c_str(), CFStringBuiltInEncodings::kCFStringEncodingUTF8);
        CFStringRef cfType = CFStringCreateWithCString(NULL, type.c_str(), CFStringBuiltInEncodings::kCFStringEncodingUTF8);

        CFURLRef appUrlRef =
        CFBundleCopyResourceURL(CFBundleGetMainBundle(), cfFile, cfType, NULL);

        CFStringRef macPath = CFURLCopyFileSystemPath(appUrlRef, kCFURLPOSIXPathStyle);
        std::string resourcePath(CFStringGetCStringPtr(macPath, CFStringGetSystemEncoding()));

        CFRelease(appUrlRef);
        CFRelease(macPath);
        CFRelease(cfType);
        CFRelease(cfFile);

        return resourcePath;
    };

    auto& texStore = GetTexStore();
    texStore.Load("wasteland_tilemap"_id, GetRenderer(), getResource("wasteland_tilemap", "png"));

    // Load Sprites
    texStore.Load("ladybug"_id, GetRenderer(), getResource("ladybug", "png"));
    texStore.Load("frog"_id, GetRenderer(), getResource("frog", "png"));

    // Load TileMap
    LoadMap(getResource("wasteland_tilemap", "layout"), "wasteland_tilemap", 4);

    auto& registry = GetRegistry();
    ladybug = registry.CreateEntity();
    registry.AddComponent<SpriteComponent>(ladybug, "ladybug", Rect2D{0, 0, 32, 32}, 1);
    registry.AddComponent<SpriteAnimationComponent>(ladybug, 0, 7, 0, 4, true);
    registry.AddComponent<TransformComponent>(ladybug, 32 * 4, 32 * 4, 2, 2);
    registry.AddComponent<RigidBodyComponent>(ladybug, 0, 1);
    registry.AddComponent<BoxCollider>(ladybug, 32*2, 32*2);

    for (int i = 0; i < 5; ++i) {
        Entity frog = registry.CreateEntity();
        registry.AddComponent<SpriteComponent>(frog, "frog", Rect2D{0, 0, 32, 32}, 1);
        registry.AddComponent<SpriteAnimationComponent>(frog, 0, 2, 0, 4, true);
        registry.AddComponent<TransformComponent>(frog, 32 * i * 3, 0 * 3, 3, 3, 0);
        registry.AddComponent<RigidBodyComponent>(frog, 1, 1);
        registry.AddComponent<BoxCollider>(frog, 32*3, 32*3);
        frogs.push_back(frog);
    }
}

void FrogTDGame::OnGameUpdate(float dt) {

}

void FrogTDGame::OnGameFixedUpdate() {

    auto bounce_on_edges = [&](RigidBodyComponent& rb, TransformComponent& tr) {
        auto offset_bounce_x = GetWidth() - 32 * tr.scale.x;
        auto offset_bounce_y = GetHeight() - 32 * tr.scale.y;

        if (tr.position.x > offset_bounce_x) {
            tr.position.x -= tr.position.x - offset_bounce_x;
            rb.velocity.x = -rb.velocity.x;
        }

        if (tr.position.x < 0) {
            tr.position.x = 0;
            rb.velocity.x = -rb.velocity.x;
        }

        if (tr.position.y > offset_bounce_y) {
            tr.position.y -= tr.position.y - offset_bounce_y;
            rb.velocity.y = -rb.velocity.y;
        }

        if (tr.position.y < 0) {
            tr.position.y = 0;
            rb.velocity.y = -rb.velocity.y;
        }
    };

    for (auto frog: frogs) {
        auto& rigid = GetRegistry().GetComponent<RigidBodyComponent>(frog);
        auto& transform = GetRegistry().GetComponent<TransformComponent>(frog);
        bounce_on_edges(rigid, transform);
    }

    auto& rigid2 = GetRegistry().GetComponent<RigidBodyComponent>(ladybug);
    auto& transform2 = GetRegistry().GetComponent<TransformComponent>(ladybug);

    bounce_on_edges(rigid2, transform2);
}

#endif //CGFX_FROGTDGAME_HPP
