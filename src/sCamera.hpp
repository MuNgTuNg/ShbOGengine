#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

#include <sWindow.hpp>

namespace shb{

class sCamera{
 public:
 
    sCamera(sWindow& window) : m_Window(window) {}
   
    //translation 
    float m_X = 0.f; float m_Y = 0.f; float m_Z=-2.f;
    glm::vec3 m_Position{m_X,m_Y,m_Z};
   
   //rotation
    glm::vec3 m_Orientation{0.f,0.f,-1.f};
    glm::vec3 m_Up{0.f,1.f,0.f};

    float m_RotX = 1.f; float m_RotY = 1.f; float m_RotZ = 1.f;
    float m_RotAngle = 1.f;



    void getInput(); //checks for keyboard inputs

   
    void update(float delta){

        getInput();

    //»»» UPDATE VARIABLES «««
      //update postion matrix

       //how fast the camera moves
        float speed = m_MoveSpeed* delta;
        //std::cout<<"Speed: " << speed << "Delta: " << delta << "\n";
        
    //»»» MATRICES «««
        //reset all matrices
        m_Model = glm::mat4(1.f);
        m_View = glm::mat4(1.f);
        m_Proj = glm::mat4(1.f);
        m_Rotation = glm::mat4(1.f);

       //the actual view of the camera
        m_View = glm::lookAt(m_Position,m_Position + m_Orientation, m_Up);
        m_Rotation = glm::rotate(glm::mat4(1.0f), m_RotAngle, glm::vec3(m_RotX,m_RotY,m_RotZ)); //TODO:: dedicate function to this

       //perspective
        setPerspective(glm::radians(m_Fov), m_Aspect,m_Near,m_Far);

    //»»» UPDATE MAIN MATRIX «««
       //creates matrix to send off to models as a uniform
        m_CameraMatrix = m_Proj*m_View;//*m_Model*m_Rotation;
    }

    //change position
    void setXYZ(float x, float y, float z){
        m_X = x;
        m_Y = y;
        m_Z = z;

    }
 
    //change visible bounds
    void setPerspective(float fov, float aspect, float near, float far){
        m_Proj = glm::perspective(fov, aspect,near,far);
    }

   //camera details

    bool m_CaptureMouse = true;
    bool m_KeyboardInput = true;
  
    //camera speed
    float m_MoveSpeed = 20.f;
    float m_LookSpeed = 50.f;
    
    //camera ddimensions
    float m_Fov = 90.f;
    float m_Near = 0.1f;
    float m_Far = 100000.f;
    float m_Aspect = 16/9;

    sWindow& m_Window;

    //matrix to pass to the shaders 
    glm::mat4 m_CameraMatrix{1.f};

    glm::mat4 m_Model{1.f};
    glm::mat4 m_View{1.f};
    glm::mat4 m_Proj{1.f};
    glm::mat4 m_Rotation{1.f};
    


};

}//namespace shb
