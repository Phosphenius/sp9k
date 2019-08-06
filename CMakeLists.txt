cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 17)
add_compile_options(-Wall -Wextra -pedantic -Werror)

project(SP9k)

set (SP9k_VERSION_MAJOR 0)
set (SP9k_VERSION_MINOR 1)
set (SP9k_VERSION_PATCH 0)

configure_file (
    "${PROJECT_SOURCE_DIR}/config.h.in"
    "${PROJECT_SOURCE_DIR}/include/config.h"
    )
 
file(GLOB_RECURSE game_FILES
    "${PROJECT_SOURCE_DIR}/include/*.h"
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
    )

include_directories("${PROJECT_SOURCE_DIR}/include")

find_package(SFML 2.5 COMPONENTS graphics window REQUIRED)
add_executable(sp9k "${game_FILES}")
target_link_libraries(sp9k sfml-graphics sfml-window)
