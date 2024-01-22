cmake_minimum_required(VERSION 3.5)

project(testgame-cpp)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "-g")

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/src/*.cpp")

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(testgame-cpp ${SOURCES})

target_link_libraries(testgame-cpp ${CURSES_LIBRARIES})

target_include_directories(testgame-cpp
  PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)
