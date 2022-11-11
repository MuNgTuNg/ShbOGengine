cmake_minimum_required(VERSION 3.13.4)

project(ShbOGEngine) #smello_world = ${PROJECT_NAME}



add_executable(${PROJECT_NAME} main.cpp)


########################### random lib
target_link_libraries(${PROJECT_NAME} shb_random) #links library to project
add_subdirectory(shb_random) #adds subdirectory
target_include_directories(${PROJECT_NAME} PUBLIC shb_random) #allows me to #include <shb_random.h> instead of #include "shb_random/shb_random.h"
target_link_directories(${PROJECT_NAME} PRIVATE shb_random) #paths from build folder
target_link_libraries(${PROJECT_NAME} shb_random) #links library to project
##############################




########################### glfw
add_subdirectory(external/glfw) #adds subdirectory
##############################
################################## add lib
add_subdirectory(shb_add) #adds subdirectory
####################################

add_subdirectory(src)

target_link_directories(${PROJECT_NAME} 
PRIVATE src
PRIVATE shb_add 
PRIVATE external/glfw/src
) #paths from build folder


target_include_directories(${PROJECT_NAME} 

PUBLIC src
PUBLIC shb_add 

PUBLIC external/glfw/include


) #allows me to #include <shb_random.h> instead of #include "shb_random/shb_random.h"

target_link_libraries(${PROJECT_NAME} shb_add glfw) #links library to project



# set(MYVAR hello_woldr) #setting variable

# function(print)
#     foreach(var ${ARGN}) #for all values(var) passed(ARGN) to function 
#         message("${var} = ${${var}}") #variable name = variable value
#     endforeach()
    
# endfunction()

#print(PROJECT_NAME PROJECT_NAME_FOO MYVAR)