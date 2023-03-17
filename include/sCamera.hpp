#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

#include <sWindow.hpp>
#include <sDebugging.hpp>

namespace shb{

class sCamera{
 public:
 
    sCamera(sWindow& window) : m_Window(window) {
        m_X = 0.f;
        m_Y = 0.f; 
        m_Z = 0.f;
    }
   
    void getInput(); //checks for keyboard inputs
    void update(float delta);
  

   //change position
    void setXYZ(float x, float y, float z){
        m_X = x;
        m_Y = y;
        m_Z = z;
        m_Position = {m_X,m_Y,m_Z};
    }
 
   //change visible bounds
    void setPerspective(float fov, float aspect, float near, float far){
        m_Proj = glm::perspective(fov, aspect,near,far);
    }


   //camera input details
    bool m_CaptureMouse = false;
    bool m_KeyboardInput = false;
  
   //camera speed
    float m_MoveSpeed = 0.01f;
    float m_MouseLookSpeed = 20.f;
    float m_KeyboardLookSpeed = 5.f;
    
   //camera dimensions
    float m_Fov = 90.f;
    float m_Near = 0.001f;
    float m_Far = 10000.f;
    float m_Aspect = 16/9;


   //matrix to pass to the shaders 
   //comprised of the view and projection multiplied together
    glm::mat4 m_CameraMatrix{1.f};
    glm::mat4 m_View{1.f};
    glm::mat4 m_Proj{1.f};

   //translation 
    float m_X = 0.f; float m_Y = 0.f; float m_Z=0.f;
    glm::vec3 m_Position{m_X,m_Y,m_Z};
   
   //rotation
    glm::vec3 m_Orientation{0.f,0.f,-1.f};
    glm::vec3 m_Up{0.f,1.f,0.f};
    float m_RotX = 0.f; float m_RotY = 0.f; float m_RotZ = 0.f;
    float m_RotAngle = 1.f;

   //references to other objects
    sWindow& m_Window;
};

}//namespace shb
