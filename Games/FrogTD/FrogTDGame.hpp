#ifndef CGFX_FROGTDGAME_HPP
#define CGFX_FROGTDGAME_HPP

#include <fstream>
#include "CGFX/CGFX.hpp"
#include "CGFX/Event/Events/InputEvents.hpp"
#include "CGFX/ECS/Components/KeyboardControllable.hpp"
#include "CGFX/ECS/Components/DebugComponent.hpp"
#include "CGFX/ECS/Components/CameraTracker.hpp"
#include "CGFX/Systems/CameraSystem.hpp"

using namespace cgfx;

class FrogTDGame final : public Game {
public:
	FrogTDGame() : Game(1920, 1080) {}

	void OnGameStart() override;
	void OnGameFixedUpdate() override;
	void
	LoadTileMapIntoRegistry(const std::string& layoutFile, const std::string& texFile, int tileSize, int tileMapsCols,
							int tileScale);
private:
	Entity ladybug{};
	std::vector<Entity> frogs;
	u32 mapHeight = 0;
	u32 mapWidth = 0;
	Logger gameLogger{"GAME"};
};

void FrogTDGame::OnGameStart() {

	auto& texStore = GetTexStore();
	texStore.Load("wasteland_tilemap"_id, GetRenderer(), GetResource("wasteland_tilemap", "png"));

	// Load Sprites
	texStore.Load("ladybug"_id, GetRenderer(), GetResource("ladybug", "png"));
	texStore.Load("frog"_id, GetRenderer(), GetResource("frog", "png"));

	// Load TileMap
	LoadTileMapIntoRegistry(GetResource("wasteland_tilemap", "layout"), "wasteland_tilemap", 32, 3, 4);

	auto& registry = GetRegistry();

	ladybug = registry.CreateEntity();
	registry.AddComponent<SpriteComponent>(ladybug, "ladybug", Rect2D{0, 0, 32, 32}, 1);
	registry.AddComponent<SpriteAnimationComponent>(ladybug, 0, 7, 0u, 4, true);
	registry.AddComponent<TransformComponent>(ladybug, 32 * 4, 32 * 4, 2, 2);
	registry.AddComponent<RigidBodyComponent>(ladybug, 0, 0);
	registry.AddComponent<BoxCollider>(ladybug, 32 * 2, 32 * 2);
	registry.AddComponent<KeyboardControllable>(ladybug, vec2{0, 300}, vec2{300, 0}, vec2{0, 300}, vec2{300, 0});
	registry.AddComponent<CameraTracker>(ladybug);

	for (int i = 0; i < 5; ++i) {
		Entity frog = registry.CreateEntity();
		registry.AddComponent<SpriteComponent>(frog, "frog", Rect2D{0, 0, 32, 32}, 1);
		registry.AddComponent<SpriteAnimationComponent>(frog, 0, 2, 0u, 4, true);
		registry.AddComponent<TransformComponent>(frog, 32 * i * 3, 0 * 3, 4, 4, 0);
		registry.AddComponent<RigidBodyComponent>(frog, 100, 100);
		registry.AddComponent<BoxCollider>(frog, 32 * 4, 32 * 4);
		frogs.push_back(frog);
	}

	GetBus().Subscribe<KeyEvent>([this, &registry](KeyEvent& event) {
	  if (event.state == KeyState::PRESSED) {
		  if (event.key == Key::P) {
			  for (auto& frog: frogs) {
				  if (!registry.HasComponent<DebugComponent>(frog)) {
					  registry.AddComponent<DebugComponent>(frog);
				  } else {
					  registry.RemoveComponent<DebugComponent>(frog);
				  }
			  }
			  if (!registry.HasComponent<DebugComponent>(ladybug)) {
				  registry.AddComponent<DebugComponent>(ladybug);
			  } else {
				  registry.RemoveComponent<DebugComponent>(ladybug);
			  }
		  } else if (event.key == Key::TAB) {
			  auto frog = frogs[frogs.size() / 2];
			  if (registry.HasComponent<CameraTracker>(frog)) {
				  registry.RemoveComponent<CameraTracker>(frog);
				  registry.RemoveComponent<KeyboardControllable>(frog);
				  registry.AddComponent<CameraTracker>(ladybug);
				  registry.AddComponent<KeyboardControllable>(ladybug, vec2{0, 300}, vec2{300, 0}, vec2{0, 300},
															  vec2{300, 0});
				  auto& rb = registry.GetComponent<RigidBodyComponent>(ladybug);
				  rb.velocity = {0,0};
				  rb.acceleration = {0,0};
			  } else {
				  registry.RemoveComponent<CameraTracker>(ladybug);
				  registry.RemoveComponent<KeyboardControllable>(ladybug);
				  registry.AddComponent<CameraTracker>(frog);
				  registry.AddComponent<KeyboardControllable>(frog, vec2{0, 300}, vec2{300, 0}, vec2{0, 300},
															  vec2{300, 0});
				  auto& rb = registry.GetComponent<RigidBodyComponent>(ladybug);
				  rb.velocity = {0,0};
				  rb.acceleration = {0,0};
			  }
		  }
	  }
	});
}

void FrogTDGame::OnGameFixedUpdate() {

	auto bounce_on_edges = [this](RigidBodyComponent& rb, TransformComponent& tr) {
	  auto offset_bounce_x = static_cast<f32>(mapWidth) - 32 * tr.scale.x;
	  auto offset_bounce_y = static_cast<f32>(mapHeight) - 32 * tr.scale.y;

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
}

void FrogTDGame::LoadTileMapIntoRegistry
		(const std::string& layoutFile, const std::string& texFile, int tileSize, int tileMapsCols, int tileScale) {
	auto& registry = GetRegistry();
	const int tile_size = tileSize;
	const int tile_map_cols = tileMapsCols;
	const int tile_scale = tileScale;
	std::ifstream map_file(layoutFile);
	std::string line;
	int x = 0;
	int y = 0;
	int line_count = 0;
	int row_count = 0;
	while (std::getline(map_file, line)) {
		std::istringstream iss(line);
		std::string index_string;
		y = 0;
		row_count = 0;
		while (std::getline(iss, index_string, ',')) {
			row_count++;
			int index = std::stoi(index_string);
			int index_x = index % tile_map_cols;
			int index_y = index / tile_map_cols;
			auto map_tile = registry.CreateEntity();
			registry.AddComponent<SpriteComponent>(map_tile, texFile, Rect2D(index_x, index_y, 32, 32), 0);
			registry.AddComponent<TransformComponent>(map_tile, y, x, tile_scale, tile_scale);
			y += tile_size * tile_scale;
		}
		x += tile_size * tile_scale;
		line_count++;
	}
	mapHeight = tile_size * tile_scale * line_count;
	mapWidth = tile_size * tile_scale * row_count;
	Rect2D map = Rect2D(GetWidth(), GetHeight(), mapWidth, mapHeight);
	registry.GetSystem<CameraSystem>().SetMapBoundaries(map);
}

#endif //CGFX_FROGTDGAME_HPP
