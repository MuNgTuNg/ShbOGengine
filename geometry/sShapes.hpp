#pragma once 
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>

// »»» VERTICES ««« 
 //vertices
 namespace shb{

//todo implement
struct sVertex{
  float x,y,z;
  float r,g,b;
  float tx,ty;
};

class sShape {
 public:
    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;
};


class sTriangle : public sShape{
 public:
    std::vector<GLfloat> vertices = 
  {
    -0.5f,     -0.5f * float(sqrt(3)) / 3,     0.0f,   0.5f, 0.0f, 0.5f,    0.0f, 0.0f, //lower left
     0.5f,     -0.5f * float(sqrt(3)) / 3,     0.0f,   0.0f, 0.5f, 0.5f,    0.0f, 1.0f, //lower right
     0.0f,      0.5f * float(sqrt(3)) *2/3,    0.0f,   0.0f, 0.0f, 1.0f,    1.0f, 1.0f,//upper right

    -0.5f/2,   0.5f * float(sqrt(3)) / 6,     0.0f,    0.5f, 0.0f, 0.5f,    0.0f, 0.0f,//inner left
     0.5f/2,   0.5f * float(sqrt(3)) / 6,     0.0f,    0.0f, 0.0f, 0.5f,   0.0f,1.0f,//inner right
     0.0f,    -0.5f * float(sqrt(3)) / 3,     0.0f,    0.0f, 0.0f, 0.5f,   1.0f, 1.0f

  
  };

    std::vector<GLuint> indices = 
  {
    0, 3, 5, //lower left
    3, 2, 4, //lower right
    5, 4, 1


  };

};



class sSquare : public sShape{
 public:
    std::vector<GLfloat> vertices = 
  { //           COORDS      / /     //    COLORS   //   TEX COORDS   //
     -0.5f,  -0.5f,  0.0f,      0.5f, 0.0f, 0.5f,      0.0f, 0.0f, //lower left
     -0.5f,   0.5f,  0.0f,      0.0f, 0.5f, 0.5f,      0.0f, 1.0f,//lower right
      0.5f,   0.5f,  0.0f,      0.0f, 0.0f, 1.0f,      1.0f, 1.0f,//upper right
      0.5f,  -0.5f,  0.0f,      1.0f, 0.0f, 1.0f,      1.0f, 0.0f //upper left
   
  
  };

    std::vector<GLuint> indices = 
  {
    0,2,1, //upper triangle
    0,3,2 //lower triangle


  };
};

class sPyramid : public sShape{
 public:
  std::vector<GLfloat> vertices =
{ //     COORDINATES     /        COLORS      /   TexCoord  //
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	2.5f, 5.0f
};
std::vector<GLuint> indices =
{
	0, 1, 2,
	0, 2, 3,
	0, 1, 4,
	1, 2, 4,
	2, 3, 4,
	3, 0, 4
};

};



}
 