cmake_minimum_required(VERSION 3.9)
project(workspace)

set(CMAKE_CXX_STANDARD 14)

add_executable(workspace main.cpp)

find_package( OpenCV REQUIRED)

target_link_libraries( workspace ${OpenCV_LIBS})
