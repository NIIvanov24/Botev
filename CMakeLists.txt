cmake_minimum_required(VERSION 3.16)
project(InventoryManagement CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Collect source files
set(SOURCES
    src/main.cpp
    src/data.cpp
    src/logic.cpp
    src/presentation.cpp
)

# Include headers
include_directories(include)

# Main executable
add_executable(inventory ${SOURCES})

# -------------------------------------------------------
# ImGui integration (uncomment when adding GUI)
# -------------------------------------------------------
# Find and link ImGui + backend (SDL2 / GLFW / etc.)
# target_sources(inventory PRIVATE
#     imgui/imgui.cpp
#     imgui/imgui_draw.cpp
#     imgui/imgui_tables.cpp
#     imgui/imgui_widgets.cpp
#     imgui/backends/imgui_impl_sdl2.cpp
#     imgui/backends/imgui_impl_opengl3.cpp
# )
# find_package(SDL2 REQUIRED)
# target_include_directories(inventory PRIVATE imgui imgui/backends)
# target_link_libraries(inventory SDL2::SDL2 GL)
