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

    float m_X = 0.f; float m_Y = 0.f; float m_Z=-2.f;
    float fov = 90.f;

    void update(){
        model = glm::mat4(1.f);
        view = glm::mat4(1.f);
        proj = glm::mat4(1.f);
        
        view = glm::translate(view, glm::vec3(m_X,m_Y,m_Z));
        setPerspective(glm::radians(fov), (float)16/9,0.1f,100000.f);
    }
    void setXYZ(float x, float y, float z){
        m_X = x;
        m_Y = y;
        m_Z = z;
    }

    void setPerspective(float fov, float aspect, float near, float far){
        proj = glm::perspective(fov, aspect,near,far);
    }


    sWindow& m_Window;
};

}//namespace shb
