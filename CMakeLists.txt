cmake_minimum_required(VERSION 3.16)
project(q3tod3_map VERSION 0.2.1 LANGUAGES C CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt6 REQUIRED COMPONENTS Gui Widgets)

qt_standard_project_setup()


add_subdirectory(src/core)
add_subdirectory(src/gui)
add_subdirectory(src/cli)
