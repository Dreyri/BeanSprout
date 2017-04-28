file(GLOB SRC_FILES *.cpp *.h)

find_package(FreeImage REQUIRED)

INCLUDE_DIRECTORIES(${FreeImage_INCLUDE_DIR})

add_library(Resource ${SRC_FILES})

target_link_libraries(Resource ${FreeImage_LIBRARIES})
