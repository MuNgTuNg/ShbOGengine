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
       add "sTexturedShape", "TextureVAO", "NormalVAO"
       MandelBrot and Julia shapes
       Each shape should have their own scale and rotation
*/
class sShape {
 public:
  void init();
  virtual void update(sCamera& camera, double delta) = 0;
  virtual void draw() = 0;
  virtual void cleanup() = 0;

  sShape(float x = 0.f, float y = 0.f, float z = 0.f){
    m_X = x;
    m_Y = y;
    m_Z = z;
  };

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
 

  std::vector<GLfloat> m_Vertices{};
  BufferObject m_VertexBuffer{}; 

  std::vector<GLuint> m_Indices{};
  BufferObject m_IndexBuffer{};
  
  //could do with some OOP here TODO::
  vertColTexVAO m_VAO{};
  


  glm::mat4 m_Model{1.f};
  glm::mat4 m_View{1.f};

  float m_X; float m_Y; float m_Z;

  GLfloat m_Scale = 1.f;

  glm::mat4 m_Rotation{};
  GLfloat m_Angle = 0.001f;
  GLfloat m_RotAxisx = 0.001f;
  GLfloat m_RotAxisy = 0.001f;
  GLfloat m_RotAxisz = 0.001f;


};

}//namespace shb
 
#include <geometry/sPyramid.hpp>
#include <geometry/sIcosohedron.hpp>
#include <geometry/sQuad.hpp>
#include <geometry/sMandelbrot.hpp>
#include <geometry/sJulia.hpp>