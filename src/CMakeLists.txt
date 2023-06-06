
include_directories(
    PUBLIC ${PARENT_DIR}../include
    PUBLIC ${PARENT_DIR}../geometry
    PUBLIC ${PARENT_DIR}../debugging    
    PUBLIC ${PARENT_DIR}../external/stb
    PUBLIC ${PARENT_DIR}../external/imgui
    PUBLIC ${PARENT_DIR}../shaders
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}

)
add_subdirectory(geometry)
add_library(src 
            sApp.cpp 
            sWindow.cpp 
            sGui.cpp
            sShader.cpp
            sCamera.cpp
            sTexture.cpp
          

)

