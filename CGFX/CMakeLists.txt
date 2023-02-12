# CGFX
add_library(CGFX STATIC
            Game/Game.hpp
            Game/Game.cpp
            Core/Logger.hpp
            Core/AlgorithmExtension.hpp
            Core/Macros.hpp
            Core/Reflection.hpp
            Assets/Texture2D.hpp
            Assets/AssetStore.hpp
            ECS/ECS.hpp
            ECS/Registry.hpp
            ECS/Exception.hpp
            ECS/Components/TransformComponent.hpp
            ECS/Components/RigidBodyComponent.hpp
            ECS/Components/SpriteComponent.hpp
            ECS/Component.hpp
            ECS/Entity.hpp
            ECS/System.hpp
            ECS/Registry.cpp
            ECS/Components/BoxCollider.hpp
            CGFX.hpp
            Core/Core.hpp
            Core/Assertions.hpp
            Core/StringId.hpp
            Core/StringId.cpp
            Core/Math.hpp
            Core/Memory.hpp
            Core/detail/MurmurHash3.hpp
            Core/detail/MurmurHash3.cpp
            Systems/PhysicsSystem.cpp
            Systems/PhysicsSystem.hpp
            Systems/SpriteRenderer.cpp
            Systems/SpriteRenderer.hpp
            Systems/AnimationSystem.cpp
            Systems/AnimationSystem.hpp
            Systems/CollisionSystem.cpp
            Systems/CollisionSystem.hpp
            Systems/detail/BoxColliderTransform.hpp
            Core/EnumFlag.hpp
            Event/EventBus.hpp Event/Events/CollisionEvent.hpp)

if (WINDOWS AND (UNIX AND NOT APPLE))
    target_compile_definitions(CGFX PRIVATE CGFX_WINDOWS)
    target_compile_definitions(CGFX PRIVATE CGFX_OPENGL)
    target_compile_definitions(CGFX PRIVATE CGFX_DIRECTX)
elseif (APPLE)
    target_compile_definitions(CGFX PRIVATE CGFX_APPLE)
    target_compile_definitions(CGFX PRIVATE CGFX_OPENGL)
    target_compile_definitions(CGFX PRIVATE CGFX_METAL)
elseif (UNIX)
    target_compile_definitions(CGFX PRIVATE CGFX_UNIX)
    target_compile_definitions(CGFX PRIVATE CGFX_OPENGL)
endif ()

target_compile_definitions(CGFX PUBLIC
                           $<$<CONFIG:Debug>:CGFX_DEBUG>
                           $<$<CONFIG:Debug>:CGFX_ASSERTIONS_ENABLED>
                           $<$<CONFIG:RelWithDebInfo>:CGFX_DEBUG>
                           $<$<CONFIG:Release>:CGFX_RELEASE>
                           $<$<CONFIG:MinSizeRel>:CGFX_RELEASE>
                           )
target_compile_options(CGFX PUBLIC $<$<CXX_COMPILER_ID:MSVC>: /EHsc>)
target_compile_options(CGFX PRIVATE $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>: -Wall> $<$<CXX_COMPILER_ID:MSVC>: /EHsc /W4>)

target_include_directories(CGFX INTERFACE SDL2::SDL2 SDL2_image::SDL2_image glm::glm)
target_link_libraries(CGFX PUBLIC SDL2::SDL2 SDL2_image::SDL2_image glm::glm Microsoft.GSL::GSL spdlog::spdlog)
