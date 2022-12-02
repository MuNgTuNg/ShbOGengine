
include_directories(
    PUBLIC ${CMAKE_CURRENT_DIR}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}

)

add_library(stb  stb_image.h stb.cpp)