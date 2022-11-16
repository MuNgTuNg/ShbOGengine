
include_directories(
    PUBLIC ${PARENT_DIR}../geometry
    PUBLIC ${PARENT_DIR}../utils
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}

)
add_library(src sApp.cpp sApp.hpp sWindow.cpp )

