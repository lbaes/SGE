
add_executable(FrogTD FrogTDGame.hpp Main.cpp)
set_target_properties(FrogTD PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(FrogTD PUBLIC CGFX)

add_custom_target(copy_assets
                  COMMENT "Copying assets..."
                  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/GameAssets $<TARGET_FILE_DIR:FrogTD>/assets
                  COMMAND_EXPAND_LISTS)

add_dependencies(FrogTD copy_assets)