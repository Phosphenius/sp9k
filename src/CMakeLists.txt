cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 17)
add_compile_options(-Wall -Wextra -pedantic -Werror)

project(sfml_starfighter)

set (sfml_starfighter_VERSION_MAJOR 0)
set (sfml_starfighter_VERSION_MINOR 1)

configure_file (
    "${PROJECT_SOURCE_DIR}/config.h.in"
    "${PROJECT_BINARY_DIR}/config.h"
    )

include_directories("${PROJECT_BINARY_DIR}")

find_package(SFML 2.5 COMPONENTS graphics window REQUIRED)
add_executable(starfighter main.cpp)
target_link_libraries(starfighter sfml-graphics sfml-window)
