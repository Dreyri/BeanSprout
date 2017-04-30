file(GLOB SRC_FILES *.cpp *.h)

find_package(FreeImage REQUIRED)
find_package(Boost COMPONENTS filesystem REQUIRED)

INCLUDE_DIRECTORIES(${FREEIMAGE_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})

add_library(Resource ${SRC_FILES})

target_link_libraries(Resource Application ${FREEIMAGE_LIBRARIES} ${Boost_LIBRARIES})
