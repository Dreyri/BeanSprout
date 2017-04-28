file(GLOB_RECURSE MATH_HEADER_FILES *.h)
#add_library(Math ${SRC_FILES})
add_custom_target(math_headers SOURCES ${MATH_HEADER_FILES})
