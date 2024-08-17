cmake_minimum_required(VERSION 3.12)
project(SPH_CPU)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)

# Set the include directories
include_directories(include)

# Add your source files here
file(GLOB SOURCES "src/*.cpp")

# Create the executable
add_executable(${PROJECT_NAME} ${SOURCES})