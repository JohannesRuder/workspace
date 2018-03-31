cmake_minimum_required(VERSION 3.9)
project(workspace)

# Toolchain file with values for the whole project (e.g. C++ 14)
include(${CMAKE_CURRENT_LIST_DIR}/CMakeConfiguration.cmake)

find_package(Qt5 COMPONENTS Core Widgets Gui Test REQUIRED)

#QtTest
enable_testing()

#add_executable(MainwindowSpec
#        test/mainwindow_spec.cpp
#        src/team.cpp
#        src/player.cpp
#        src/video.cpp
#        src/camera.cpp
#        src/action.cpp
#        src/game.cpp
#        src/gym.cpp
#        mainwindow.cpp
##        src/opencvworker.cpp
#        src/rally.cpp
#        src/season.cpp
#        src/set.cpp
#        src/utils.cpp)

#add_test(MainwindowSpec mainwindow_spec)
#target_link_libraries(MainwindowSpec Qt5::Widgets Qt5::Test)

#Get all header files in the directory
file(GLOB QT_GEN_HEADERS ./bin_debug/*.h)
file(GLOB QT_CPP_GENERATED ./bin_debug/*.cpp)

add_executable(workspace main.cpp
        src/team.cpp
        src/player.cpp
        src/video.cpp
        src/camera.cpp
        src/action.cpp
        src/game.cpp
        src/gym.cpp
        mainwindow.cpp
#        src/opencvworker.cpp
        src/rally.cpp
        src/season.cpp
        src/set.cpp
        src/utils.cpp
        ui_mainwindow.h
        ${QT_GEN_HEADERS}
        ${QT_CPP_GENERATED})

qt5_use_modules(workspace Core Widgets Gui)

# OpenCV
find_package(OpenCV REQUIRED)
target_link_libraries(workspace ${OpenCV_LIBS})
#target_link_libraries(MainwindowSpec ${OpenCV_LIBS})

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
        test/video_spec.cpp src/video.cpp
        test/utils_spec.cpp src/utils.cpp)

# Link test executable against gtest & gtest_main
target_link_libraries(runUnitTests
        gtest gtest_main
        ${OpenCV_LIBS}
        Qt5::Core Qt5::Widgets Qt5::Gui)

set(QT_GENERATED qtGenerated)
add_custom_target(${QT_GENERATED})
add_dependencies(${PROJECT_NAME} ${QT_GENERATED})

#Copy them to the project dir
foreach(QT_GEN_HEADERS ${QT_GEN_HEADERS})
    add_custom_command(TARGET ${QT_GENERATED} PRE_BUILD COMMAND
            ${CMAKE_COMMAND} -E copy_if_different
            ${QT_GEN_HEADERS} ${CMAKE_SOURCE_DIR})
endforeach()

target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Widgets Qt5::Gui)

## Include what you use
#find_program(iwyu_path NAMES include-what-you-use iwyu)
#if(NOT iwyu_path)
#    message(FATAL_ERROR "Could not find the program include-what-you-use")
#endif()
#
#set(iwyu_path_and_options
#        ${iwyu_path}
#        -Xiwyu
#        --verbose=1)
##        --mapping_file=${my_mapping})
#
#set_property(TARGET ${PROJECT_NAME}
#        PROPERTY CXX_INCLUDE_WHAT_YOU_USE ${iwyu_path_and_options})
