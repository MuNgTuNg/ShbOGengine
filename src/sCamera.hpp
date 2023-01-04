#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <sWindow.hpp>

namespace shb{

class sCamera{
 public:
 
    sCamera(sWindow& window) : m_Window(window) {}
    glm::mat4 model{1.f};
    glm::mat4 view{1.f};
    glm::mat4 proj{1.f};
    glm::mat4 rotation{1.f};
    
    //translation 
    float m_X = 0.f; float m_Y = 0.f; float m_Z=-2.f;
    glm::vec3 m_Position{m_X,m_Y,m_Z};
   
   //rotation
    glm::vec3 m_Orientation{0.f,0.f,-1.f};
    glm::vec3 m_Up{0.f,1.f,0.f};

    float m_RotX = 1.f; float m_RotY = 1.f; float m_RotZ = 1.f;
    float m_RotAngle = 90.f;

   
    void update(float delta){

        getInput();

        
       //reset all matrices
        model = glm::mat4(1.f);
        view = glm::mat4(1.f);
        proj = glm::mat4(1.f);
        rotation = glm::mat4(1.f);

      //update postion matrix
        m_Position = {m_X,m_Y,m_Z};

       //how fast the camera moves
        float speed = m_MoveSpeed* delta;
        //std::cout<<"Speed: " << speed << "Delta: " << delta << "\n";
        
       //the actual view of the camera
        view = glm::lookAt(m_Position,m_Position + m_Orientation, m_Up);
        rotation = glm::rotate(glm::mat4(1.0f), m_RotAngle, glm::vec3(m_RotX,m_RotY,m_RotZ)); //TODO:: dedicate function to this

       //perspective
        setPerspective(glm::radians(fov), aspect,m_Near,m_Far);

       //creates matrix to send off to models as a uniform
        cameraMatrix = proj*view*model*rotation;
    }
    void setXYZ(float x, float y, float z){
        m_X = x;
        m_Y = y;
        m_Z = z;
    }

    void setPerspective(float fov, float aspect, float near, float far){
        proj = glm::perspective(fov, aspect,near,far);
    }

   //camera details
    float fov = 90.f;
    float m_MoveSpeed = 20.f;
    float m_Near = 0.1f;
    float m_Far = 100000.f;
    float aspect = 16/9;

    sWindow& m_Window;
    glm::mat4 cameraMatrix{1.f};



    void getInput();
};

}//namespace shb
