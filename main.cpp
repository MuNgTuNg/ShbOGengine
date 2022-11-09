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

int main(int argc, char*argv[]){
  


 
  if (!glfwInit())
  {
    fprintf(stderr, "Failed to initialize GLFW\n");
    exit(EXIT_FAILURE);
  }
  
      

  GLFWwindow* window;

  if( argv[1]!= NULL && strcmp(argv[1], "fullscreen") == 0){
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    window = glfwCreateWindow(1000, 1000, "Fullscreen window", monitor, NULL);
   }
   else{
    window = glfwCreateWindow(1000, 1000, "Windowed window", NULL, NULL);

   }
   glfwMakeContextCurrent(window);

   
   gladLoadGL();

   glViewport(0,0,1000,1000);

   glClearColor(255,255,3,1);
  

   //loop
    while (!glfwWindowShouldClose(window))
    {
        glfwSwapBuffers(window);
         glClear(GL_COLOR_BUFFER_BIT);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
  
  return 0;
}
