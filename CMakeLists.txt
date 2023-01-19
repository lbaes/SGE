cmake_minimum_required(VERSION 3.24)
set(CMAKE_CXX_STANDARD 20)
project(CGFX)

# DEPENDENCIES
include(FetchContent)
FetchContent_Declare(
        sdl
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG f17058b562c8a1090c0c996b42982721ace90903
        GIT_SHALLOW ON
)

FetchContent_Declare(
        sdl_image
        GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
        GIT_TAG a861543ab78f5d5e18e6af43964ce8df60cb30b3
        GIT_SHALLOW ON
)

FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm.git
        #GIT_TAG bf71a834948186f4097caa076cd2663c69a10e1e
        GIT_SHALLOW ON
)

FetchContent_Declare(
        GSL
        GIT_REPOSITORY "https://github.com/microsoft/GSL"
        GIT_TAG "v4.0.0"
        GIT_SHALLOW ON
)

FetchContent_Declare(
        spdlog
        GIT_REPOSITORY "https://github.com/gabime/spdlog.git"
        GIT_TAG "ad0e89cbfb4d0c1ce4d097e134eb7be67baebb36"
        GIT_SHALLOW ON
)

set(SDL2IMAGE_INSTALL OFF CACHE BOOL "" FORCE)
set(SDL2TTF_INSTALL OFF CACHE BOOL "" FORCE)
set(SDL2NET_INSTALL OFF CACHE BOOL "" FORCE)
set(SDL2IMAGE_SAMPLES OFF CACHE BOOL "" FORCE)
set(SDL2NET_SAMPLES OFF CACHE BOOL "" FORCE)
set(SDL2TTF_SAMPLES OFF CACHE BOOL "" FORCE)
set(SDL2MIXER_SAMPLES OFF CACHE BOOL "" FORCE)
set(SDL2TTF_VENDORED ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(sdl sdl_image glm GSL spdlog)

# CGFX
add_subdirectory(CGFX)

# APPS
add_subdirectory(Games)

target_include_directories(CGFX PUBLIC ./)