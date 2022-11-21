cmake_minimum_required(VERSION 3.13.4)


project(ShbOGEngine LANGUAGES CXX C ) #ShbOGEngine = ${PROJECT_NAME}
add_executable(${PROJECT_NAME} main.cpp)


#adding subdirectories to be used (they contain cmakeLists files that add them as libraries)
add_subdirectory(geometry)
add_subdirectory(external/glfw)
add_subdirectory(external)
add_subdirectory(utils) 
add_subdirectory(src)

#shows where to look for libraries, looks for CMakeLists.txt with add_library() or add_executable() commands
target_link_directories(${PROJECT_NAME} 
PRIVATE src
PRIVATE utils 
PRIVATE external/glfw/src
PRIVATE geometry
PRIVATE external
) 

#adds subdirectories to the global include path e.g: #include <sApp.hpp>  (sApp.hpp is in src)
target_include_directories(${PROJECT_NAME} 
PUBLIC src
PUBLIC utils 
PUBLIC geometry
PUBLIC external/glfw/include
PUBLIC external
) 

#links libraires together to be compiled into the executable (i think)
target_link_libraries(${PROJECT_NAME} 
src 
utils 
geometry 
glfw
stb
) 



# set(MYVAR hello_woldr) #setting variable

# function(print)
#     foreach(var ${ARGN}) #for all values(var) passed(ARGN) to function 
#         message("${var} = ${${var}}") #variable name = variable value
#     endforeach()
    
# endfunction()

#print(PROJECT_NAME PROJECT_NAME_FOO MYVAR)