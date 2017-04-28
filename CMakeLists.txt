cmake_minimum_required (VERSION 2.6)
project(BeanSprout)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

SET(INCLUDE_DIRS "/opt/local/include")
FILE(GLOB_RECURSE LibFiles "src/signal/*.h")
add_custom_target(headers SOURCES ${LibFiles})

find_library(GLFWLIB glfw)

INCLUDE_DIRECTORIES(${BeanSprout_SOURCE_DIR}/src)
include_directories(${INCLUDE_DIRS})

SET(CLANG_CXX1Z_SUPPORT "-std=c++14")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CLANG_CXX1Z_SUPPORT}")

add_subdirectory(src)
add_subdirectory(test)
