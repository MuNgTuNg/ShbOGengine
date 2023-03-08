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
       PLEASE FIND A BETTER WAY TO ADD NEW SHAPES
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

  void setXYZ(float x, float y, float z){
    m_X = x;
    m_Y = y;
    m_Z = z;
  }

  std::vector<GLfloat> m_Vertices;
  std::vector<GLuint> m_Indices;
  BufferObject m_VertexBuffer{}; 
  BufferObject m_IndexBuffer{};
  defaultVAO m_VAO{};

  float m_X; float m_Y; float m_Z;
  glm::mat4 m_Model{1.f};
  glm::mat4 m_View{1.f};

};







}//namespace shb
 
#include <sPyramid.hpp>
#include <sIcosohedron.hpp>
