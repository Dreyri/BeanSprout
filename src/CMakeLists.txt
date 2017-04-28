add_subdirectory(graphics)
add_subdirectory(input)
add_subdirectory(math)
add_subdirectory(signal)
add_subdirectory(util)

add_library(Application application.cpp)
message(STATUS ${GRAPHICS_SRC_FILES})
add_executable(test_input testInput.cpp input/input_manager.cpp graphics/window.cpp)

target_link_libraries(test_input ${GLFWLIB} Input Graphics)
