find_package(GIF)

IF(GIF_FOUND)
INCLUDE_DIRECTORIES(${GIF_INCLUDE_DIR})
ENDIF()

file(GLOB GRAPHICS_SRC_FILES *.cpp)

add_library(Graphics ${GRAPHICS_SRC_FILES})
target_link_libraries(Graphics ${GLFWLIB})
