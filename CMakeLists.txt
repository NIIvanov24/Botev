cmake_minimum_required(VERSION 3.16)
project(BotevInventory LANGUAGES CXX)

# -------------------------------------------------------
# Standards & compiler options
# -------------------------------------------------------
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Enable stricter warnings in debug builds
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    if (MSVC)
        add_compile_options(/W4)
    else()
        add_compile_options(-Wall -Wextra -Wpedantic)
    endif()
endif()

# -------------------------------------------------------
# Source files
# -------------------------------------------------------
set(SOURCES
    src/main.cpp
    src/data.cpp
    src/logic.cpp
    src/ui.cpp
)

add_executable(botev ${SOURCES})
target_include_directories(botev PRIVATE include)

# -------------------------------------------------------
# Raylib integration
# -------------------------------------------------------
# Option A: Raylib installed system-wide (Linux/macOS via package manager)
#   sudo apt install libraylib-dev        (Ubuntu / Debian)
#   brew install raylib                   (macOS)
#
# Option B: FetchContent (downloads and builds Raylib automatically)
#
# Uncomment ONE of the blocks below:

# ----- Option A: find_package (system-installed Raylib) -----
find_package(raylib 5.0 QUIET)
if (raylib_FOUND)
    message(STATUS "Found system Raylib: ${raylib_VERSION}")
    target_link_libraries(botev PRIVATE raylib)
endif()

# ----- Option B: FetchContent (auto-download Raylib 5.0) -----
if (NOT raylib_FOUND)
    include(FetchContent)
    FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG        5.0
        GIT_SHALLOW    TRUE
    )
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(raylib)
    target_link_libraries(botev PRIVATE raylib)
    message(STATUS "Raylib 5.0 will be downloaded via FetchContent")
endif()

# -------------------------------------------------------
# Platform-specific extras
# -------------------------------------------------------
if (APPLE)
    target_link_libraries(botev PRIVATE
        "-framework IOKit"
        "-framework Cocoa"
        "-framework OpenGL")
elseif (UNIX)
    target_link_libraries(botev PRIVATE GL m pthread dl rt X11)
elseif (WIN32)
    target_link_libraries(botev PRIVATE winmm)
    # Suppress console window in Release builds on Windows
    if (CMAKE_BUILD_TYPE STREQUAL "Release")
        set_target_properties(botev PROPERTIES WIN32_EXECUTABLE TRUE)
    endif()
endif()

# -------------------------------------------------------
# Copy assets next to the executable after build
# -------------------------------------------------------
add_custom_command(TARGET botev POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:botev>/assets
    COMMENT "Copying assets to build directory"
)

# -------------------------------------------------------
# Installation
# -------------------------------------------------------
install(TARGETS botev DESTINATION bin)
install(DIRECTORY assets/ DESTINATION bin/assets)
