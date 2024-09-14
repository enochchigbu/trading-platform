# Specify the minimum CMake version required
cmake_minimum_required(VERSION 3.30.3)

# Set the project name and version
project(MyProject VERSION 1.0)

# Specify the C++ standard to use
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable target
add_executable(MyExecutable main.cpp)

# Optionally, link any libraries if needed
