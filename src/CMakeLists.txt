find_package(GLM)

IF(GLM_FOUND)
    INCLUDE_DIRECTORIES(${GLM_INCLUDE_DIRS})
ENDIF()

set(BeanSprout_DEBUG true)

configure_file(
    "${PROJECT_SOURCE_DIR}/src/beansproutconfig.h.in"
    "${PROJECT_BINARY_DIR}/src/beansproutconfig.h")

INCLUDE_DIRECTORIES("${PROJECT_BINARY_DIR}/src")


add_subdirectory(graphics)
add_subdirectory(input)
add_subdirectory(signal)
add_subdirectory(util)

add_library(Application application.cpp)
message(STATUS ${GRAPHICS_SRC_FILES})
add_executable(test_input testInput.cpp input/input_manager.cpp graphics/window.cpp)

target_link_libraries(test_input ${GLFWLIB} Input Graphics)
