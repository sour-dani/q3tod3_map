cmake_minimum_required(VERSION 3.16)
project(q3tod3_map VERSION 0.2.2 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

string(TOLOWER "${CMAKE_SYSTEM_PROCESSOR}-${CMAKE_SYSTEM_NAME}-${CMAKE_CXX_COMPILER_ID}" COMPILE_INFO)
set(PROJECT_GITHUB_URL "https://github.com/sour-dani/q3tod3_map")
set(PROJECT_ORGANIZATION_NAME "Sour Dani")
set(LEGACY_AUTHOR "motorsep")

configure_file("${CMAKE_SOURCE_DIR}/src/core/config.h.in" "${CMAKE_SOURCE_DIR}/src/core/config.h")

find_package(Qt6 REQUIRED COMPONENTS Gui Widgets)
qt_standard_project_setup()

add_subdirectory(src/gui)
add_subdirectory(src/cli)
