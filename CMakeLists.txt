
cmake_minimum_required(VERSION 3.28)
project(sandtetris LANGUAGES CXX)

# sets where the executable will live
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# CMake grabs and builds the whole SFML library
include(FetchContent)
FetchContent_Declare(raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 5.5  # latest stable version
)
FetchContent_MakeAvailable(raylib)

# this tells CMake to make the compile_commands.json inside out build folder 
# the JSON file contains every compiler command CMake uses
# then tools like vscodes C++ extension can then read it and know where headers live, what defines are active etc
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# here we tell CMake to add all .cpp and .h files for src to the executable file
file(GLOB_RECURSE SOURCES "src/*.cpp" "include/*.h")
add_executable(sandtetris ${SOURCES})

# here we tell CMake where we store our headers
target_include_directories(sandtetris PRIVATE include)

# here we tell CMake were using C++20
target_compile_features(sandtetris PRIVATE cxx_std_20)

# Enable compiler warnings for better code quality
target_compile_options(sandtetris PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/W4>
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic>
)

# this tells CMake to link the following librarys to the executable file
target_link_libraries(sandtetris raylib)

