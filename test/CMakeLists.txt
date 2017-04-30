enable_testing()

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

add_executable(testWindow test_window.cpp)
target_link_libraries(testWindow Graphics Input ${GIF_LIBRARIES})

file(COPY img DESTINATION ${CMAKE_CURRENT_BINARY_DIR})


if(Boost_FOUND)
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
    LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})
    add_executable(testSignals test_signal.cpp)
    add_executable(testResource test_resource.cpp)
    add_executable(testResourceManager test_resourceManager.cpp)
    target_link_libraries(testSignals ${Boost_LIBRARIES})
    target_link_libraries(testResource ${Boost_LIBRARIES})
    target_link_libraries(testResourceManager Resource Graphics Input ${Boost_LIBRARIES})
    add_test(signals testSignals)
    add_test(resource testResource)
    add_test(resourceManager testResourceManager)
endif()







