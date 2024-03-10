# Set CMake minimum version and project name
cmake_minimum_required(VERSION 3.28)
project(2048_ai_models)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the directories where the compiler can find the header files
include_directories(${PROJECT_SOURCE_DIR})

# Add executable target with source files
add_executable(GameExecutable 2048.cpp alpha_beta.cpp board.cpp)

# Link any external libraries if necessary
# target_link_libraries(GameExecutable library_name)

set(CMAKE_BUILD_TYPE Debug)
