#include <sCamera.hpp>

namespace shb{


void sCamera::getInput(){

   //»»» KEYBOARD MOVEMENT «««
    if(glfwGetKey(m_Window.handle(),GLFW_KEY_W) == GLFW_PRESS){
      m_Position += m_MoveSpeed * m_Orientation;
    }
    if(glfwGetKey(m_Window.handle(),GLFW_KEY_S) == GLFW_PRESS){
      m_Position += m_MoveSpeed * -m_Orientation;
    }
    if(glfwGetKey(m_Window.handle(),GLFW_KEY_A) == GLFW_PRESS){
      m_Position += m_MoveSpeed * -glm::normalize(glm::cross(m_Orientation,m_Up));
    }
    if(glfwGetKey(m_Window.handle(),GLFW_KEY_D) == GLFW_PRESS){
      m_Position += m_MoveSpeed * glm::normalize(glm::cross(m_Orientation,m_Up));
    }
    if(glfwGetKey(m_Window.handle(),GLFW_KEY_SPACE) == GLFW_PRESS){
      m_Position += m_MoveSpeed * m_Up;
    }
    if(glfwGetKey(m_Window.handle(),GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS){
      m_Position += m_MoveSpeed * -m_Up;
    }




  // »»» KEYBOARD ROTATION «««
    if(glfwGetKey(m_Window.handle(),GLFW_KEY_UP) == GLFW_PRESS){
      m_RotX += m_LookSpeed * (float)(m_RotY - (m_Window.height()/2)) / m_Window.height();      
    }
    if(glfwGetKey(m_Window.handle(),GLFW_KEY_DOWN) == GLFW_PRESS){
      m_RotX -= m_LookSpeed * (float)(-m_RotY - (m_Window.height()/2)) / m_Window.height();
    }
    if(glfwGetKey(m_Window.handle(),GLFW_KEY_LEFT) == GLFW_PRESS){
      m_RotY += m_LookSpeed * (float)(m_RotX - (m_Window.height()/2)) / m_Window.height();
    }
    if(glfwGetKey(m_Window.handle(),GLFW_KEY_RIGHT) == GLFW_PRESS){
      m_RotY -= m_LookSpeed * (float)(-m_RotX - (m_Window.height()/2)) / m_Window.height();
    }


  //»»» MOUSE ROTATION «««
    if(glfwGetMouseButton(m_Window.handle(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS){
      glfwSetInputMode(m_Window.handle(),GLFW_CURSOR,GLFW_CURSOR_HIDDEN);

      if(m_CaptureMouse){
        glfwSetCursorPos(m_Window.handle(), (m_Window.width()/2), (m_Window.height()/2));
      }
      
        double mouseX;
        double mouseY;
        glfwGetCursorPos(m_Window.handle(), &mouseX, &mouseY);
  
  
        float rotY = m_LookSpeed * (float)(mouseX - (m_Window.width()/2)) / m_Window.width();
        float rotX = m_LookSpeed * (float)(mouseY - (m_Window.height()/2)) / m_Window.height();      
        
        glm::vec3 newOrientation = glm::rotate(m_Orientation, glm::radians(-rotX), glm::normalize(glm::cross(m_Orientation, m_Up)));


        if(   !(glm::angle(newOrientation,m_Up) <= glm::radians(5.0f))    ||    glm::angle(newOrientation,-m_Up) <= glm::radians(5.0f))    {
         m_Orientation = newOrientation;
        }
      
        m_Orientation = glm::rotate(m_Orientation, glm::radians(-rotY),m_Up);
		    glfwSetCursorPos(m_Window.handle(), (m_Window.width() / 2), (m_Window.height() / 2));
        

    }
    else if(glfwGetMouseButton(m_Window.handle(), GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS && m_CaptureMouse ){
        glfwSetInputMode(m_Window.handle(),GLFW_CURSOR,GLFW_CURSOR_NORMAL);
        m_CaptureMouse = false;
    }



  // »»» UPDATE CURRENT ORIENTATION 

    
    
    
    m_Orientation = glm::rotate(m_Orientation, glm::radians(-m_RotY),m_Up);

    //reset rotation values each frame
    m_RotY = m_RotX = m_RotZ = 0;
    
    
}

}//namespace shb