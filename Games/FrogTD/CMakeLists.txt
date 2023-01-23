set(RESOURCE_FILES
    GameAssets/frog.png
    GameAssets/ladybug.png
    GameAssets/wasteland_tilemap.layout
    GameAssets/wasteland_tilemap.png)

add_executable(FrogTD FrogTDGame.hpp Main.cpp "${RESOURCE_FILES}")

set_target_properties(FrogTD PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(FrogTD PROPERTIES
                      MACOSX_BUNDLE TRUE
                      MACOSX_FRAMEWORK_IDENTIFIER org.cgfx.FrogTD
                      RESOURCE "${RESOURCE_FILES}")

target_link_libraries(FrogTD PUBLIC CGFX "-framework CoreFoundation")

#add_custom_target(copy_assets
#                  COMMENT "Copying assets..."
#                  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/GameAssets $<TARGET_FILE_DIR:FrogTD>/assets
#                  COMMAND_EXPAND_LISTS)
#
#add_dependencies(FrogTD copy_assets)