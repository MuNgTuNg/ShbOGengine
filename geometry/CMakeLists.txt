include_directories(
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
    PUBLIC ${PARENT_DIR}../src
    PUBLIC ${PARENT_DIR}../utils 
    
    PUBLIC ${PARENT_DIR}../external/stb
)
add_library(geometry sShapes.hpp sShapes.cpp)