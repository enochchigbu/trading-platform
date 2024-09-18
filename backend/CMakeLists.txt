# Specify the minimum CMake version required
cmake_minimum_required(VERSION 3.30.3)

# Set the project name and version
project(MyProject VERSION 1.0)

# Specify the C++ standard to use
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable target
add_executable(server server.cpp)

# Add the path to the Crow and ASIO headers
include_directories(/opt/homebrew/Cellar/asio/1.30.2/include)
include_directories(/opt/homebrew/include/Crow/include/crow)
include_directories(/opt/homebrew/include/Crow/include)
include_directories(/opt/homebrew/include)

# Link against ASIO and pthread
target_link_libraries(server PRIVATE pthread)

# Optionally, link any libraries if needed