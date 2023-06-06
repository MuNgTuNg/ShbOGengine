#include <sMetaApp.hpp>
#include <sWindow.hpp>

namespace shb{

class sMandelApp : public sMetaApp{

 public:
    sMandelApp(sCamera& camera, sWindow& window) : m_Window(window), m_Camera(camera){
        mandel.listenWindow(&window);
        //mandel.listenCamera(&camera);
        objects.push_back(new sJulia{0.f,0.f,-1.f});
    }
    void getInput(){
        if(glfwGetKey(m_Window.handle(),GLFW_KEY_W) == GLFW_PRESS || glfwGetKey(m_Window.handle(),GLFW_KEY_SPACE) == GLFW_PRESS){
            if(mandel.render){ //TODO:: implement this in imgui so that i can choose from a gui
              mandel.offsetY += m_Camera.m_MoveSpeed;
            }
            if(julia.render){
              julia.offsetY += m_Camera.m_MoveSpeed;
            }
        }
    
        if(glfwGetKey(m_Window.handle(),GLFW_KEY_A) == GLFW_PRESS){
          if(julia.render){
            julia.offsetX -= m_Camera.m_MoveSpeed;
          }
          if(mandel.render){
            mandel.offsetX -= m_Camera.m_MoveSpeed;
          }
        }
        if(glfwGetKey(m_Window.handle(),GLFW_KEY_S)  == GLFW_PRESS|| glfwGetKey(m_Window.handle(),GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS){
            julia.offsetY -= m_Camera.m_MoveSpeed;
        }
        if(glfwGetKey(m_Window.handle(),GLFW_KEY_D) == GLFW_PRESS){
            julia.offsetX += m_Camera.m_MoveSpeed;
        }

        if(glfwGetKey(m_Window.handle(),GLFW_KEY_U) == GLFW_PRESS){
            julia.m_Zoom -= m_Camera.m_MoveSpeed;
        }
        if(glfwGetKey(m_Window.handle(),GLFW_KEY_J) == GLFW_PRESS){
            julia.m_Zoom += m_Camera.m_MoveSpeed;
        }

        //update julia offset
        if(glfwGetKey(m_Window.handle(),GLFW_KEY_I) == GLFW_PRESS){
            julia.juliaX += 0.005;
        }
        if(glfwGetKey(m_Window.handle(),GLFW_KEY_K) == GLFW_PRESS){
            julia.juliaX -= 0.005;
        }
        if(glfwGetKey(m_Window.handle(),GLFW_KEY_O) == GLFW_PRESS){
            julia.juliaY += 0.005;
        }
        if(glfwGetKey(m_Window.handle(),GLFW_KEY_L) == GLFW_PRESS){
            julia.juliaY -= 0.005;
        }

    }


    void run() {
        

    }
    void cleanup() {
        
    }
    void update(sCamera& camera, double delta) {
        
        //mandel.update(camera,delta);
        //mandel.draw();
        julia.update(camera,delta);
        julia.draw();
    }
    void update() {
        
    }

    sMandelbrot mandel{0.f,0.f,-1.f};
   
    bool juliaStart = true;
    sJulia julia{0.f,0.f,-1.f};

    sWindow& m_Window;
    sCamera& m_Camera;

};
}//namespace shb