#include <sCamera.hpp>

namespace shb{


void sCamera::getInput(){

   //WSAD forward back left right
    if(glfwGetKey(m_Window.handle(),GLFW_KEY_W) == GLFW_PRESS){
      m_Z += m_MoveSpeed;
    }
    if(glfwGetKey(m_Window.handle(),GLFW_KEY_S) == GLFW_PRESS){
      m_Z -= m_MoveSpeed;
    }
    if(glfwGetKey(m_Window.handle(),GLFW_KEY_A) == GLFW_PRESS){
      m_X += m_MoveSpeed;
    }
    if(glfwGetKey(m_Window.handle(),GLFW_KEY_D) == GLFW_PRESS){
      m_X -= m_MoveSpeed;
    }

    //up, down
    if(glfwGetKey(m_Window.handle(),GLFW_KEY_SPACE) == GLFW_PRESS){
      m_Y -= m_MoveSpeed;
    }
    if(glfwGetKey(m_Window.handle(),GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS){
      m_Y += m_MoveSpeed;
    }

    //rotation
    if(glfwGetKey(m_Window.handle(),GLFW_KEY_UP) == GLFW_PRESS){
      m_RotZ -= m_MoveSpeed;
    }
    if(glfwGetKey(m_Window.handle(),GLFW_KEY_DOWN) == GLFW_PRESS){
      m_RotZ += m_MoveSpeed;
    }
    if(glfwGetKey(m_Window.handle(),GLFW_KEY_LEFT) == GLFW_PRESS){
      m_RotX += m_MoveSpeed;
    }
    if(glfwGetKey(m_Window.handle(),GLFW_KEY_RIGHT) == GLFW_PRESS){
      m_RotX -= m_MoveSpeed;
    }
    
}

}//namespace shb