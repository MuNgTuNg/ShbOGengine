cmake_minimum_required(VERSION 3.13.4)


project(ShbOGEngine LANGUAGES CXX C ) #ShbOGEngine = ${PROJECT_NAME}
add_executable(${PROJECT_NAME} main.cpp)


#adding subdirectories to be used (they contain cmakeLists files that add them as libraries)
add_subdirectory(debugging) 
add_subdirectory(external/glfw)
add_subdirectory(external/stb)
add_subdirectory(external/imgui)
add_subdirectory(include)
add_subdirectory(src)


#add_subdirectory(geometry)

#shows where to look for libraries, looks for CMakeLists.txt with add_library() or add_executable() commands
target_link_directories(${PROJECT_NAME} 
PRIVATE external/glfw/src
PRIVATE external/stb
PRIVATE external/imgui
PRIVATE incl
PRIVATE src
PRIVATE debugging

PRIVATE include/geometry
PRIVATE src/geometry


) 


#adds subdirectories to the global include path e.g: #include <sApp.hpp>  (sApp.hpp is in src)
target_include_directories(${PROJECT_NAME} 
PUBLIC external/glfw/include
PUBLIC external/stb
PUBLIC external/imgui
PUBLIC include/geometry
PUBLIC src/geometry
PUBLIC include
PUBLIC src
PUBLIC debugging

) 

#these reference eachother so must be linked both ways
target_link_libraries(
    debugging
    src 
    SrcGeometry
    InclGeometry
)
target_link_libraries( 
    InclGeometry
    SrcGeometry
    incl
    src
    debugging
    imgui
    stb
     
)
#links libraires together to be compiled into the executable (i think)
target_link_libraries(${PROJECT_NAME} 
debugging
InclGeometry 
SrcGeometry
incl
src 
imgui
glfw
stb

) 
target_link_libraries( 
    debugging
)


