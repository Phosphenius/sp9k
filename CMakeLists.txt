cmake_minimum_required(VERSION 3.13)

set(CMAKE_CXX_STANDARD 17)
add_compile_options(-Wall -Wextra -pedantic -Werror)
IF(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif(NOT CMAKE_BUILD_TYPE)

project(SP9k)

set (SP9k_VERSION_MAJOR 0)
set (SP9k_VERSION_MINOR 1)
set (SP9k_VERSION_PATCH 0)

IF(NOT SP9k_ASSET_ROOT_PATH)
    set(SP9k_ASSET_ROOT_PATH "${PROJECT_SOURCE_DIR}")
endif(NOT SP9k_ASSET_ROOT_PATH)

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

install(TARGETS sp9k RUNTIME DESTINATION bin)
install(DIRECTORY "${PROJECT_SOURCE_DIR}/gfx" "${PROJECT_SOURCE_DIR}/fonts" DESTINATION share/sp9k)
install(FILES "${PROJECT_SOURCE_DIR}/sp9k.desktop" DESTINATION share/applications)
install(FILES "${PROJECT_SOURCE_DIR}/LICENSE" DESTINATION share/licenses/sp9k)
