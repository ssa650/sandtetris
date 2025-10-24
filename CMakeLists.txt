
cmake_minimum_required(VERSION 3.28)
project(sandtetris LANGUAGES CXX)

# sets where the executable will live
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# CMake grabs and builds the whole SFML library
include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.2
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

# this tells CMake to make the compile_commands.json inside out build folder 
# the JSON file contains every compiler command CMake uses
# then tools like vscodes C++ extension can then read it and know where headers live, what defines are active etc
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# here we give CMake the files we want the compile and what directories they live in
add_executable(main src/main.cpp)

# here we tell CMake were using C++20
target_compile_features(main PRIVATE cxx_std_20)

# this tells CMake to link the following librarys to the executable file
target_link_libraries(main PRIVATE SFML::Graphics)