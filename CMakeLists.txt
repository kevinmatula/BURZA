cmake_minimum_required(VERSION 3.16)
project(BURZA)
set(SOURCES
    src/main.cpp
    src/core/Window.cpp
    src/core/Application.cpp
    src/core/ApplicationInit.cpp
    src/rendering/Renderer.cpp
    src/rendering/Shader.cpp
    src/rendering/Mesh.cpp
    src/input/InputManager.cpp
    src/world/Entity.cpp
    src/world/Scene.cpp
    src/world/Camera.cpp
    src/math/Transform.cpp
    src/interface/Game.cpp
    src/rendering/MeshLoader.cpp
    src/config/Settings.cpp
    external/glad/src/glad.c
    nedolia/src/Nedolia.cpp
)

# Generate build/compile_commands.json so clangd can resolve include paths like
# <SDL3/SDL.h>.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# set the output directory for built objects. This makes sure that the dynamic
# library goes into the build directory automatically.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

add_subdirectory(external/SDL EXCLUDE_FROM_ALL)
add_subdirectory(external/glm EXCLUDE_FROM_ALL)

# Create your game executable target as usual
add_executable(${CMAKE_PROJECT_NAME} WIN32 ${SOURCES})

target_include_directories(
    ${CMAKE_PROJECT_NAME}
    PRIVATE include external/glad/include external/tinyobjloader
)

# Link to the actual SDL3 library.
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE SDL3::SDL3)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE glm::glm)

add_custom_command(
    TARGET ${CMAKE_PROJECT_NAME}
    POST_BUILD
    COMMAND
        ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>/assets
    COMMENT "Copying assets/ into BURZA binary"
)
