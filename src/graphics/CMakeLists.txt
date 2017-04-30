find_package(GIF)
find_package(OpenGL)

IF(GIF_FOUND)
INCLUDE_DIRECTORIES(${GIF_INCLUDE_DIR})
ENDIF()

if(OPENGL_FOUND)
    INCLUDE_DIRECTORIES(${OPENGL_INCLUDE_DIR})
endif()

file(GLOB GRAPHICS_SRC_FILES *.cpp)

add_library(Graphics ${GRAPHICS_SRC_FILES})
target_link_libraries(Graphics ${GLFWLIB} ${OPENGL_LIBRARIES})
