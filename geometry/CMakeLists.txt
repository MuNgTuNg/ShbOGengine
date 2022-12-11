include_directories(
    PUBLIC ${CMAKE_CURRENT_DIR}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}

)
add_library(geometry sShapes.hpp sShapes.cpp)