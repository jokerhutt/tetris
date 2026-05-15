cmake_minimum_required(VERSION 3.16)
project(tetris)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

# Dependencies

FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 5.5
)

FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG docking
)

FetchContent_Declare(
    rlimgui
    GIT_REPOSITORY https://github.com/raylib-extras/rlImGui.git
    GIT_TAG main
)

FetchContent_MakeAvailable(raylib imgui rlimgui)

# ImGui

add_library(imgui_lib
    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp
)

target_include_directories(imgui_lib PUBLIC
    ${imgui_SOURCE_DIR}
)

# ------------------------
# App
# ------------------------

add_library(rlimgui_lib

    ${rlimgui_SOURCE_DIR}/rlImGui.cpp

)

target_include_directories(rlimgui_lib PUBLIC

    ${rlimgui_SOURCE_DIR}

    ${imgui_SOURCE_DIR}

)

target_link_libraries(rlimgui_lib PUBLIC

    raylib

    imgui_lib

)

add_executable(tetris
    src/main.cpp
    src/position.cpp
    src/grid.cpp
    src/colors.cpp
    src/block.cpp
    src/blocks.cpp
    src/game.cpp
    src/ui.cpp
)

target_include_directories(tetris PRIVATE
    ${rlimgui_SOURCE_DIR}
)

# LINK THAT SONOFABITCH

target_link_libraries(tetris PRIVATE
    rlimgui_lib
)
