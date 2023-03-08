
include_directories(
    PUBLIC ${PARENT_DIR}../geometry
    PUBLIC ${PARENT_DIR}../debugging    
    PUBLIC ${PARENT_DIR}../external/stb
    PUBLIC ${PARENT_DIR}../external/imgui
    PUBLIC ${PARENT_DIR}../shaders
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}

)
add_library(incl INTERFACE
            sApp.hpp 
            sWindow.hpp 
            sGui.hpp
            sShader.hpp
            sCamera.hpp
)
