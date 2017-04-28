enable_testing()

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

add_executable(testWindow test_window.cpp)
target_link_libraries(testWindow Graphics Input ${GIF_LIBRARIES})


if(Boost_FOUND)
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
    LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})
    add_executable(testSignals test_signal.cpp)
    add_executable(testVector test_vector.cpp)
    add_executable(testMatrix test_matrix.cpp)
    target_link_libraries(testSignals ${Boost_LIBRARIES})
    target_link_libraries(testVector ${Boost_LIBRARIES} )
    target_link_libraries(testMatrix ${Boost_LIBRARIES})
    add_test(signals testSignals)
    add_test(vector testVector)
    add_test(matrix testMatrix)
endif()







