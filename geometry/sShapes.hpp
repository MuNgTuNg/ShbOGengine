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
 void update(glm::mat4 model, glm::mat4 view, glm::mat4 proj, double delta);
 void cleanup();

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
sShader fragShader{};
sShader vertShader{};


// »»» SHADER PROGRAM «««  
  //shader program is an executable to be used on the gpu
sShaderProgram m_ShaderProgram1{};

    //»»» TEXTURES «««


 //name of uniform doesnt seem to matter? todo
int makimaTextureSlot = 0;
sTexture makimaTexture{"makima","makima.jpeg", GL_TEXTURE_2D,GL_RGB, makimaTextureSlot};

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
float fov = 45.f;

GLfloat scale = 1.f;
GLfloat angle = 0.1f;
GLfloat rotAxisx = 0.1f;
GLfloat rotAxisy = 0.1f;
GLfloat rotAxisz = 0.1f;

bool scalePeaked = false;

GLuint scaleUniform = 0;
GLuint rotationMatrixUniform = 0;




};



}
 