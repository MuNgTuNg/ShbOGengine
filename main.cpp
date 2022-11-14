//
//
//
//
//
//  TODO: » abstract and clean up
//        » logging system
//        » change shader system to use string instead of VECTORS????
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
#include <sApp.hpp>
#include <shader_utils.cpp>
#include <shapes.h>         //vertices etc

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

  GLint isCompiled = 0;
  glGetShaderiv(fragShader, GL_COMPILE_STATUS, &isCompiled);
  if(isCompiled == GL_FALSE)
{
	GLint maxLength = 0;
	glGetShaderiv(fragShader, GL_INFO_LOG_LENGTH, &maxLength);

	// The maxLength includes the NULL character
	std::vector<GLchar> errorLog(maxLength);
	glGetShaderInfoLog(fragShader, maxLength, &maxLength, &errorLog[0]);

  for(GLchar word : errorLog){
    std::cout << word;
  }
	// Provide the infolog in whatever manor you deem best.
	// Exit with failure.
	glDeleteShader(fragShader); // Don't leak the shader.
	
}

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




// »»» BUFFERS «««
  GLuint VAO, VBO, IBO;
  glGenVertexArrays(1,&VAO); //generate before vertex buffer (essentially manages vertex attributes)
  glGenBuffers(1, &VBO);               //inits buffer handles (can be array) »[num of buffers, pointer to buffers]

  glGenBuffers(1, &IBO);
  
  glBindVertexArray(VAO); 

  glBindBuffer(GL_ARRAY_BUFFER, VBO);  //specifies usage of buffer and allows handle to be used »[usage of buffer, buffer handle]
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),vertices, GL_STATIC_DRAW); //allocates and fills currently bound buffer and specifies usage [DYNAMIC,STATIC,STREAM][DRAW,READ,COPY]
  
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
  
  glVertexAttribPointer(0,3, GL_FLOAT,GL_FALSE, 3* sizeof(float), (void*)0); //tell opengl how we want to feed it to the shader we are using (how it's formatted)
  glEnableVertexAttribArray(0); //tell opengl to use slot 0 for the shader
  
  glBindBuffer(GL_ARRAY_BUFFER, 0); //unbind so they cannot be modified after the fact 
  glBindVertexArray(0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


// »»» RENDERING LOOP «««

//set the viewport            todo:: viewport does not draw whole screen in fullscreen mode
  glViewport(0,0,height,width);

  float r = 0;
  float g = 0;
  float b = 0;
  
  //»»» MAIN LOOP «««
  while (!glfwWindowShouldClose(window))
  {
    
    r += 0.001;
    g += 0.003;
    b += 0.004;
    if(r >= 1){
      r = 0;
    }
    if(g >= 1){
      g = 0;
    }
    if(b >= 1){
      b = 0;
    }
   
    glBindVertexArray(VAO);      //says that we want to feed the shader this specific way
    glUseProgram(shaderProgram); //uses executable created earlier
    
    //set clear color
    
    glClearColor(r,g,b,1.f);
    
    glClear(GL_COLOR_BUFFER_BIT);

    glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT , 0); //[PRIMITIVE, OFFSET, NUMBER TO DRAW]
   
   //swap buffers
    glfwSwapBuffers(window); 

   
    
   
   //poll events
    glfwPollEvents();           //have any window events happened? 
  }
  
 //cleanup
  glDeleteVertexArrays(1, & VAO);
  glDeleteBuffers(1,&VBO);
  glDeleteBuffers(1,&IBO);
  glDeleteProgram(shaderProgram);
  glfwDestroyWindow(window);
  glfwTerminate();
  
  return 0;
}
