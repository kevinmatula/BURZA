cmake_minimum_required(VERSION 3.16)
project(BURZA)

# Generate build/compile_commands.json so clangd can resolve
# include paths like <SDL3/SDL.h>.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# set the output directory for built objects.
# This makes sure that the dynamic library goes into the build directory automatically.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

add_subdirectory(external/SDL EXCLUDE_FROM_ALL)

# Create your game executable target as usual
add_executable(${CMAKE_PROJECT_NAME} WIN32 src/main.cpp external/glad/src/glad.c)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE external/glad/include)

# Link to the actual SDL3 library.
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE SDL3::SDL3)
