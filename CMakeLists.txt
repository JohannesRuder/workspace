cmake_minimum_required(VERSION 3.9)
project(workspace)

set(CMAKE_CXX_STANDARD 14)

add_executable(workspace main.cpp)

# OpenCV
find_package(OpenCV REQUIRED)
target_link_libraries(workspace ${OpenCV_LIBS})

# Googletest
# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND "${CMAKE_COMMAND}" -G "${CMAKE_GENERATOR}" .
        WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/googletest-download" )
execute_process(COMMAND "${CMAKE_COMMAND}" --build .
        WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/googletest-download" )

# Add googletest directly to our build. This adds
# the following targets: gtest, gtest_main, gmock
# and gmock_main
add_subdirectory("${CMAKE_BINARY_DIR}/googletest-src"
        "${CMAKE_BINARY_DIR}/googletest-build")

# Googletest
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTest_SOURCE_DIR}/include ${GTest_SOURCE_DIR})

# Add test cpp file
add_executable(runUnitTests test/unittest.cpp)

# Link test executable against gtest & gtest_main
target_link_libraries(runUnitTests gtest gtest_main)
