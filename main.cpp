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
#include <iostream>
#include <chrono>
#include <shb_random.h> 
#include <shb_add.h>   
#include <GLFW/glfw3.h> 

int main(){
  std::cout<<"hello world\n";

  for(int i = 0; i< 10; i++){
    long int time = TIME; //TIME = macro defined in random.h
    std::cout<< shbRandom(time) << " ";
  }
  std::cout<<"\n" << shb_add(32, 32);

  std::cout<<"\n";

  GLFWwindow* window;

  if (!glfwInit())
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
        exit(EXIT_FAILURE);
    }


  window = glfwCreateWindow(500, 500, "Particle Engine", NULL, NULL);

  
    while (!glfwWindowShouldClose(window))
    {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
  
  return 0;
}
