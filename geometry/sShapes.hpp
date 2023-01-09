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
#include <sDebugging.hpp>
#include <sCamera.hpp>

namespace shb{

/*
TODO:: add more shapes
*/



class sShape {
 public:
    void init();
    void update(sCamera& camera, double delta);
    void cleanup();
    sShape(float x = 0.f, float y = 0.f, float z = 0.f){
      m_X = x;
      m_Y = y;
      m_Z = z;
    };
    std::vector<GLfloat> m_Vertices;
    std::vector<GLuint> m_Indices;
    void setXYZ(float x, float y, float z){
      m_X = x;
      m_Y = y;
      m_Z = z;
    }

  float m_X; float m_Y; float m_Z;
  defaultVAO m_VAO{};
  BufferObject m_VertexBuffer{}; 
  BufferObject m_IndexBuffer{};
  glm::mat4 m_Model{1.f};
  glm::mat4 m_View{1.f};

};


class sPyramid : public sShape{
 public:
 
 sPyramid(float x, float y, float z) : sShape(x,y,z) {}
 void init();
 void update(sCamera& camera, double delta);
 void cleanup();


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

// »»»»»»»»»»»»»»»»»»»»»»»»»»»»» SHADERS «««««««««««««««««««««««
//[TYPE OF SHADER, FILEPATH, COMPILE ON CREATION, SET SOURCE ON CREATION]
static sShader fragShader;
static sShader vertShader;


// »»» SHADER PROGRAM «««  
  //shader program is an executable to be used on the gpu
static sShaderProgram m_ShaderProgram;

//»»» TEXTURES «««
static int m_TextureSlot;
static sTexture m_Texture;

//»»»SQUARE update VARIABLES«««



GLfloat m_Scale = 100.f;
float m_ScaleSpeed = 10.f;
bool m_ScalePeaked = false;
float m_ScalePeak = 50.f;


glm::mat4 m_Rotation{};

GLfloat m_Angle = 0.1f;
GLfloat m_RotAxisx = 0.1f;
GLfloat m_RotAxisy = 0.1f;
GLfloat m_RotAxisz = 0.1f;


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


}//namespace shb
 

// struct sVertex{
//   float x,y,z;
//   float r,g,b;
//   float tx,ty;
// };