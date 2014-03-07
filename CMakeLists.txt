cmake_minimum_required (VERSION 2.6)

SET(CMAKE_CXX_FLAGS "-std=c++0x")

project (Sim2D)
add_executable (sim2d main.cpp Object.cpp State.cpp Derivative.cpp)

add_subdirectory(lua/)

include_directories (${LUA_INCLUDE_DIRS})
target_link_libraries (sim2d liblua)
