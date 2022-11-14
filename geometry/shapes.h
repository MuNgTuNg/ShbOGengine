#pragma once 
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

// »»» VERTICES ««« 
 //vertices
  GLfloat vertices[] = 
  {
    -0.5f,     -0.5f * float(sqrt(3)) / 3,     0.0f, //lower left
     0.5f,     -0.5f * float(sqrt(3)) / 3,     0.0f, //lower right
     0.0f,      0.5f * float(sqrt(3)) *2/3,    0.0f, //upper

    -0.5f/2,   0.5f * float(sqrt(3)) / 6,     0.0f, //inner left
     0.5f/2,   0.5f * float(sqrt(3)) / 6,     0.0f, //inner right
     0.0f,    -0.5f * float(sqrt(3)) / 3,     0.0f

  
  };

  GLuint indices[] = 
  {
    0, 3, 5, //lower left
    3, 2, 4, //lower right
    5, 4, 1

  };