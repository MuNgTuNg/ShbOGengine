//
//
//
//
//
//  TODO:
//       
//
//
//
//
//

//std
#include <iostream>
#include <string.h>

//mine
#include <hi.cpp> 

//external
#include <glad.c>
#include <GLFW/glfw3.h> 

#define HEIGHT 1000
#define WIDTH 1000

int main(int argc, char*argv[]){
  
 //initialise glfw
  if (!glfwInit())
  {
    fprintf(stderr, "Failed to initialize GLFW\n");
    exit(EXIT_FAILURE);
  }
  

  
      
 //create window
  GLFWwindow* window;
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  if( argv[1]!= NULL && strcmp(argv[1], "fullscreen") == 0){
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    window = glfwCreateWindow(HEIGHT, WIDTH, "Fullscreen window", monitor, NULL);
   }
   else{
    window = glfwCreateWindow(1000, 1000, "Windowed window", NULL, NULL);

   }
   
  //make window context current
   glfwMakeContextCurrent(window);
 

  //glad is loaded on current context so it must be after window creation and 
  //contextualisation
   gladLoadGL();
  

  //set the viewport
   glViewport(0,0,HEIGHT,WIDTH);
  //set clear color
   glClearColor(0.5f,0.5f,0.1f,1.0f);
  

   //loop
    while (!glfwWindowShouldClose(window))
    {
        glfwSwapBuffers(window);
         glClear(GL_COLOR_BUFFER_BIT);
        glfwPollEvents();
    }
  
    glfwDestroyWindow(window);
    glfwTerminate();
  
  return 0;
}
