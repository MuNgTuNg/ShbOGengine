#pragma once 
#include <glad/glad.h>
#include <GLFW/glfw3.h>

//maths
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

#include <sTexture.hpp>
#include <sBuffer.hpp>
#include <sShader.hpp>
#include <sUtils.hpp>
#include <sCamera.hpp>
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
    std::vector<GLfloat> m_Vertices = 
  {
    -0.5f,     -0.5f * float(sqrt(3)) / 3,     0.0f,   0.5f, 0.0f, 0.5f,    0.0f, 0.0f, //lower left
     0.5f,     -0.5f * float(sqrt(3)) / 3,     0.0f,   0.0f, 0.5f, 0.5f,    0.0f, 1.0f, //lower right
     0.0f,      0.5f * float(sqrt(3)) *2/3,    0.0f,   0.0f, 0.0f, 1.0f,    1.0f, 1.0f,//upper right

    -0.5f/2,   0.5f * float(sqrt(3)) / 6,     0.0f,    0.5f, 0.0f, 0.5f,    0.0f, 0.0f,//inner left
     0.5f/2,   0.5f * float(sqrt(3)) / 6,     0.0f,    0.0f, 0.0f, 0.5f,   0.0f,1.0f,//inner right
     0.0f,    -0.5f * float(sqrt(3)) / 3,     0.0f,    0.0f, 0.0f, 0.5f,   1.0f, 1.0f

  
  };

    std::vector<GLuint> m_Indices = 
  {
    0, 3, 5, //lower left
    3, 2, 4, //lower right
    5, 4, 1


  };

};



class sSquare : public sShape{
 public:
    std::vector<GLfloat> m_Vertices = 
  { //           COORDS      / /     //    COLORS   //   TEX COORDS   //
     -0.5f,  -0.5f,  0.0f,      0.5f, 0.0f, 0.5f,      0.0f, 0.0f, //lower left
     -0.5f,   0.5f,  0.0f,      0.0f, 0.5f, 0.5f,      0.0f, 1.0f,//lower right
      0.5f,   0.5f,  0.0f,      0.0f, 0.0f, 1.0f,      1.0f, 1.0f,//upper right
      0.5f,  -0.5f,  0.0f,      1.0f, 0.0f, 1.0f,      1.0f, 0.0f //upper left
   
  
  };

    std::vector<GLuint> m_Indices = 
  {
    0,2,1, //upper triangle
    0,3,2 //lower triangle


  };
};

class sPyramid : public sShape{
 public:
 sPyramid(float x = 0.f, float y = 0.f, float z = 0.f){
  m_X = x;
  m_Y = y;
  m_Z = z;
 };
 void init();
 void update(sCamera& camera, double delta);
 void cleanup();

 void setXYZ(float x, float y, float z){
    m_X = x;
    m_Y = y;
    m_Z = z;
 }
 void setScale(float scale){
    m_Scale = scale;
 }
 void rotate(){ //TODO 

 }

  std::vector<GLfloat> m_Vertices =
{ //     COORDINATES     /        COLORS      /   TexCoord  //
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	2.5f, 5.0f
};
std::vector<GLuint> m_Indices =
{
	0, 1, 2,
	0, 2, 3,
	0, 1, 4,
	1, 2, 4,
	2, 3, 4,
	3, 0, 4
};


//buffers and vertex usage
defaultVAO m_VAO{};
BufferObject m_SquareVertexBuffer{}; 
BufferObject m_SquareIndexBuffer{};

// »»»»»»»»»»»»»»»»»»»»»»»»»»»»» SHADERS «««««««««««««««««««««««
//[TYPE OF SHADER, FILEPATH, COMPILE ON CREATION, SET SOURCE ON CREATION]
static sShader fragShader;
static sShader vertShader;


// »»» SHADER PROGRAM «««  
  //shader program is an executable to be used on the gpu
static sShaderProgram m_ShaderProgram;

//»»» TEXTURES «««
 //name of uniform doesnt seem to matter? todo
static int m_TextureSlot;
static sTexture m_Texture;

//»»»SQUARE update VARIABLES«««
float m_X = 0.f;
float m_Y = 0.f;
float m_Z = -2.f;
  /*
  //create a texture 
  Params:
    1. Name in which it will be sent to the shader
    2. Name of file to be used
    3. Type of texture
    4. Format of texture
    5. Texture slot in which it will be used
  */

GLfloat m_Scale = 100.f;
float m_ScaleSpeed = 10.f;
bool m_ScalePeaked = false;
float m_ScalePeak = 50.f;

glm::mat4 m_LocalView;

GLfloat m_Angle = 0.1f;
GLfloat m_RotAxisx = 0.1f;
GLfloat m_RotAxisy = 0.1f;
GLfloat m_RotAxisz = 0.1f;
glm::mat4 m_Rotation{};

static bool initOnce;


};





//icosohedron vertices, wrong tex coords
//   std::vector<GLfloat> m_Vertices =
// { //     COORDINATES     /        COLORS      /   TexCoord  //
//   0.000f,  0.000f,  1.000f, 1.f,1.f,1.f,  0.0f,1.f,
// 	0.894f,  0.000f,  0.447f, 1.f,1.f,1.f,  -0.5f,5.f,
// 	0.276f,  0.851f,  0.447f, 1.f,1.f,1.f, 0.5f,0.f,
// 	-0.724f,  0.526f,  0.447f, 1.f,1.f,1.f,-0.5f,5.f,
// 	-0.724f, -0.526f,  0.447f, 1.f,1.f,1.f, 0.5f,0.f,
// 	0.276f, -0.851f,  0.447f, 1.f,1.f,1.f,-0.5f,5.f,
// 	0.724f,  0.526f, -0.447f, 1.f,1.f,1.f, 0.5f,0.f,
// 	-0.276f,  0.851f, -0.447f, 1.f,1.f,1.f,-0.5f,5.f,
// 	-0.894f,  0.000f, -0.447f, 1.f,1.f,1.f, 0.5f,0.f,
// 	-0.276f, -0.851f, -0.447f, 1.f,1.f,1.f,-0.5f,5.f,
// 	0.724f, -0.526f, -0.447f, 1.f,1.f,1.f, 0.5f,0.f,
// 	0.000f,  0.000f, -1.000f,  1.f,1.f,1.f, 0.5f,0.f,
// };
// std::vector<GLuint> m_Indices =
// {
//   2, 1, 0,
// 	3, 2, 0,
// 	4, 3, 0,
// 	5, 4, 0,
// 	1, 5, 0,
// 	11, 6,  7,
// 	11, 7,  8,
// 	11, 8,  9,
// 	11, 9,  10,
// 	11, 10, 6,
// 	1, 2, 6,
// 	2, 3, 7,
// 	3, 4, 8,
// 	4, 5, 9,
// 	5, 1, 10,
// 	2,  7, 6,
// 	3,  8, 7,
// 	4,  9, 8,
// 	5, 10, 9,
// 	1, 6, 10 
// };

}
 