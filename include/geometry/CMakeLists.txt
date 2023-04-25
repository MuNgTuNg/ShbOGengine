
include_directories(    PUBLIC ${PARENT_DIR}../debug ) 

include_directories(
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
    PUBLIC ${PARENT_DIR}../../src
    PUBLIC ${PARENT_DIR}../../debugging 
    PUBLIC ${PARENT_DIR}
    PUBLIC ${PARENT_DIR}../../include
    PUBLIC ${PARENT_DIR}../../external/stb
)
add_library(InclGeometry 
            sShapes.hpp 
            sPyramid.hpp
            sIcosohedron.hpp
            sQuad.hpp
            sMandelbrot.hpp
            sJulia.hpp 
            )