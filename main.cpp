//
//
//
//
//
//  TODO: » clean up a bit
//        » figure out why it crashes one in ten times?
//
//
//
//
//

//std
#include <iostream>
#include <fstream>
#include <string.h>


//mine
#include <hi.cpp> 
#include <sApp.hpp>
#include <shader_utils.cpp>

//external
#include <glad.c>
#include <GLFW/glfw3.h> 
#include <glm/glm.hpp>




int main(int argc, char*argv[]){


//  shb::sApp app; //TODO

//  app.run();st

// »»» INIT «««
 //initialise glfw
  if (!glfwInit())
  {
    fprintf(stderr, "Failed to initialize GLFW\n");
    exit(EXIT_FAILURE);
  }
  
// »»» WINDOW «««
 //tell opengl what min and max version we are using
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

 //tell opengl we're using the core profile (only using the modern functions)
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

 //create window
  GLFWwindow* window;
  int height = 1000, width = 1000;

 //get the handle to the primary monitor and get details about said moniter
  GLFWmonitor* monitor = glfwGetPrimaryMonitor();
  const GLFWvidmode* videomode = glfwGetVideoMode(monitor);

 //set to fullscreen or windowed based on command line arguments
  if( argv[1]!= NULL && strcmp(argv[1], "fullscreen") == 0)
  {
    height = videomode->height;
    width = videomode->width;
    window = glfwCreateWindow(height, width, "Fullscreen window", monitor, NULL);
  }
  else
  {
    window = glfwCreateWindow(height, width, "Windowed window", NULL, NULL);
  }


 //make window context current
  glfwMakeContextCurrent(window);
 

 //glad is loaded on current context so it must be after window creation and 
 //contextualisation
  gladLoadGL();
  
 
// »»» SHADERS «««
 //create shader source code
  //fragShader
  auto fragCode =  createShaderSource("../shaders/fragment_shader.frag");
  const char* fragShaderSource = reinterpret_cast<const char*>(fragCode.data());
  GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);  //creates handle
  glShaderSource(fragShader, 1, &fragShaderSource, NULL);  //handle, number of strings for source, source code, array of string lengths  
  glCompileShader(fragShader);                             //compiles shader

  //vertShader
  auto vertCode =  createShaderSource("../shaders/vertex_shader.vert");
  const char* vertShaderSource = reinterpret_cast<const char*>(vertCode.data());
  GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertShader, 1, &vertShaderSource, NULL);
  glCompileShader(vertShader);

  GLuint shaderProgram = glCreateProgram(); //creates a program object to which you can attach a shader object
  glAttachShader(shaderProgram,vertShader); //specifies shader objects that will be linked to create a program
  glAttachShader(shaderProgram,fragShader); //can check compatibility of shaders

  glLinkProgram(shaderProgram);  //links program to create executables to run on processors (vertex, fragment, geometry)

  glDeleteShader(fragShader); //no longer need shaders
  glDeleteShader(vertShader);


// »»» VERTICES ««« 
 //vertices
  GLfloat vertices[] = 
  {
    -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
    0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
    0.0f, 0.5f * float(sqrt(3)) *2/3, 0.0f
  };

// »»» BUFFERS «««
  GLuint VAO, VBO;
  glGenVertexArrays(1,&VAO); //generate before vertex buffer (essentially manages vertex attributes)
  glGenBuffers(1, &VBO);               //inits buffer handles (can be array) »[num of buffers, pointer to buffers]

  glBindVertexArray(VAO); 

  glBindBuffer(GL_ARRAY_BUFFER, VBO);  //specifies usage of buffer and allows handle to be used »[usage of buffer, buffer handle]
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),vertices, GL_STATIC_DRAW); //allocates and fills currently bound buffer and specifies usage [DYNAMIC,STATIC,STREAM][DRAW,READ,COPY]
  
  glVertexAttribPointer(0,3, GL_FLOAT,GL_FALSE, 3* sizeof(float), (void*)0); //tell opengl how we want to feed it to the shader we are using (how it's formatted)
  glEnableVertexAttribArray(0); //tell opengl to use slot 0 for the shader
  
  glBindBuffer(GL_ARRAY_BUFFER, 0); //unbind so they cannot be modified after the fact 
  glBindVertexArray(0);


// »»» RENDERING LOOP «««

//set the viewport            todo:: viewport does not draw whole screen in fullscreen mode
  glViewport(0,0,height,width);


  
  //»»» MAIN LOOP «««
  while (!glfwWindowShouldClose(window))
  {
    
    glBindVertexArray(VAO);      //says that we want to feed the shader this specific way
    glUseProgram(shaderProgram); //uses executable created earlier
    
    //set clear color
    glClearColor(1.f,0.f,1.f,1.f); 
    glClear(GL_COLOR_BUFFER_BIT);

    glDrawArrays(GL_TRIANGLES, 0 , 3); //[PRIMITIVE, OFFSET, NUMBER TO DRAW]
   
   //swap buffers
    glfwSwapBuffers(window); 
   
   //poll events
    glfwPollEvents();           //have any window events happened? 
  }
  
 //cleanup
  glDeleteVertexArrays(1, & VAO);
  glDeleteBuffers(1,&VBO);
  glDeleteProgram(shaderProgram);
  glfwDestroyWindow(window);
  glfwTerminate();
  
  return 0;
}
