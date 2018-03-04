cmake_minimum_required(VERSION 3.9)
project(workspace)

# Toolchain file with values for the whole project (e.g. C++ 14)
include(${CMAKE_CURRENT_LIST_DIR}/CMakeConfiguration.cmake)

# QT
# Tell CMake to run moc when necessary:
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
# As moc files are generated in the binary dir, tell CMake
# to always look for includes there:
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5 COMPONENTS Core Widgets Gui Test REQUIRED)

#QtTest
enable_testing()

add_executable(MainwindowSpec
        test/mainwindow_spec.cpp
        src/team.cpp
        src/player.cpp
        src/video.cpp
        src/camera.cpp
        src/action.cpp
        src/game.cpp
        src/gym.cpp
        src/mainwindow.cpp
        src/opencvworker.cpp
        src/rally.cpp
        src/season.cpp
        src/set.cpp)

add_test(MainwindowSpec mainwindow_spec)
target_link_libraries(MainwindowSpec Qt5::Widgets Qt5::Test)

add_executable(workspace src/main.cpp
        src/team.cpp
        src/player.cpp
        src/video.cpp
        src/camera.cpp
        src/action.cpp
        src/game.cpp
        src/gym.cpp
        src/mainwindow.cpp
        src/opencvworker.cpp
        src/rally.cpp
        src/season.cpp
        src/set.cpp)

qt5_use_modules(workspace Core Widgets Gui)

# OpenCV
find_package(OpenCV REQUIRED)
target_link_libraries(workspace ${OpenCV_LIBS})
target_link_libraries(MainwindowSpec ${OpenCV_LIBS})

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
add_executable(runUnitTests
        test/player_spec.cpp src/player.cpp
        test/team_spec.cpp src/team.cpp
        test/camera_spec.cpp src/camera.cpp
        test/action_spec.cpp src/action.cpp
        test/game_spec.cpp src/game.cpp
        test/rally_spec.cpp src/rally.cpp
        test/season_spec.cpp src/season.cpp
        test/set_spec.cpp src/set.cpp
        test/video_spec.cpp src/video.cpp)

# Link test executable against gtest & gtest_main
target_link_libraries(runUnitTests
        gtest gtest_main
        ${OpenCV_LIBS}
        Qt5::Core Qt5::Widgets Qt5::Gui)
