set(RESOURCE_FILES
    GameAssets/frog.png
    GameAssets/ladybug.png
    GameAssets/wasteland_tilemap.layout
    GameAssets/wasteland_tilemap.png)
if(WIN32)
    add_executable(FrogTD FrogTDGame.hpp Main.cpp "${RESOURCE_FILES}")
else()
    add_executable(FrogTD FrogTDGame.hpp Main.cpp "${RESOURCE_FILES}")
endif()

set_target_properties(FrogTD PROPERTIES LINKER_LANGUAGE CXX)

if (APPLE)
    set_target_properties(FrogTD PROPERTIES
                          MACOSX_BUNDLE TRUE
                          MACOSX_FRAMEWORK_IDENTIFIER org.cgfx.FrogTD
                          RESOURCE "${RESOURCE_FILES}")
    target_link_libraries(FrogTD PUBLIC CGFX "-framework CoreFoundation")
elseif (WIN32)
    target_link_libraries(FrogTD PUBLIC CGFX)
    add_custom_target(copy_assets
                      COMMENT "Copying assets..."
                      COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/GameAssets $<TARGET_FILE_DIR:FrogTD>/assets
                      COMMAND_EXPAND_LISTS)
    add_custom_target(COPY_ENGINE_DLL
      COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:FrogTD> $<TARGET_FILE_DIR:FrogTD>
      COMMAND_EXPAND_LISTS)

    add_dependencies(COPY_ENGINE_DLL CGFX)
    add_dependencies(FrogTD copy_assets COPY_ENGINE_DLL)
endif ()