#include <sCamera.hpp>

namespace shb{


void sCamera::getInput(){
 //»»» KEYBOARD MOVEMENT «««
  
  //m_Orientation starts at {0.f,0.f,-1.f} so it is looking down the Z Axis (which is negative 1)
  
  if(m_KeyboardInput){
    //Forward and backwards
    if(glfwGetKey(m_Window.handle(),GLFW_KEY_W) == GLFW_PRESS){
      m_Position += m_MoveSpeed * m_Orientation;  //changes xyz position by increasing Z axis by delta movespeed scalar
    }
    if(glfwGetKey(m_Window.handle(),GLFW_KEY_S) == GLFW_PRESS){
      m_Position += m_MoveSpeed * -m_Orientation;  //travels backwards, multiplied by deltaTime movespeed scalar
    }
  
    //Left and right                                         
    //the normalised cross product of where you are LOOKING (m_Orientation(x,y,z)) and the constant m_Up vector (0, 1, 0)
    //m_Orientation changes and updates to follow where you are looking
    //returns a perpendicular RIGHT vector (positive X axis)
    if(glfwGetKey(m_Window.handle(),GLFW_KEY_A) == GLFW_PRESS){
      m_Position += m_MoveSpeed * -glm::normalize(glm::cross(m_Orientation,m_Up));
    }                             //^^^^^^^^^^ Negative X axis ^^^^^^^^^^^^^^^^
    if(glfwGetKey(m_Window.handle(),GLFW_KEY_D) == GLFW_PRESS){
      m_Position += m_MoveSpeed * glm::normalize(glm::cross(m_Orientation,m_Up));
    }                             //^^^^^^^^^^^ Positive X axis ^^^^^^^^^^^^^^^
  
    //Up and Down
    if(glfwGetKey(m_Window.handle(),GLFW_KEY_SPACE) == GLFW_PRESS){
      m_Position += m_MoveSpeed * m_Up;
    }
    if(glfwGetKey(m_Window.handle(),GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS){
      m_Position += m_MoveSpeed * -m_Up;
  }
  }

 //"capture" mouse
  if(glfwGetKey(m_Window.handle(), GLFW_KEY_C) == GLFW_PRESS){
      m_CaptureMouse = true;
      glfwSetInputMode(m_Window.handle(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);  
  }
  if(glfwGetKey(m_Window.handle(), GLFW_KEY_X) == GLFW_PRESS && m_CaptureMouse){
      m_CaptureMouse = false;
      glfwSetInputMode(m_Window.handle(),GLFW_CURSOR,GLFW_CURSOR_NORMAL);
  }
    

 // »»» KEYBOARD ROTATION ««« 
  if(!m_CaptureMouse){
     if(glfwGetKey(m_Window.handle(),GLFW_KEY_UP) == GLFW_PRESS){
       m_RotX += m_KeyboardLookSpeed * (float)(m_RotY - (m_Window.width()/2)) / m_Window.width();
     }
     if(glfwGetKey(m_Window.handle(),GLFW_KEY_DOWN) == GLFW_PRESS){
       m_RotX -= m_KeyboardLookSpeed * (float)(-m_RotY - (m_Window.width()/2)) / m_Window.width();
     }
     if(glfwGetKey(m_Window.handle(),GLFW_KEY_LEFT) == GLFW_PRESS){
       m_RotY += m_KeyboardLookSpeed * (float)(m_RotX - (m_Window.height()/2)) / m_Window.height();
     }
     if(glfwGetKey(m_Window.handle(),GLFW_KEY_RIGHT) == GLFW_PRESS){
       m_RotY -= m_KeyboardLookSpeed * (float)(-m_RotX - (m_Window.height()/2)) / m_Window.height();
     }
  }


  

 //»»» MOUSE ROTATION «««
  if(m_CaptureMouse){
   //get details about mouse location
    double mouseX;
    double mouseY;
    glfwGetCursorPos(m_Window.handle(), &mouseX, &mouseY);
  
   //update rotation values by multiplying ??? (research)
    m_RotY = m_MouseLookSpeed * (float)(mouseX - (m_Window.width()/2)) / m_Window.width() ;
    m_RotX = m_MouseLookSpeed * (float)(mouseY - (m_Window.height()/2)) / m_Window.height();      
   //Create buffer orientation, to do prelim checks as to wether it is suitable
    //calculates VERTICAL change in rotation
    glm::vec3 newOrientation = glm::rotate(m_Orientation, glm::radians(-m_RotX), glm::normalize(glm::cross(m_Orientation, m_Up)));

   //Decide if it's legal or not 
    //basically, bounding the up and down rotations to 10 degrees from top and bottom
    if(   !(glm::angle(newOrientation,m_Up) <= glm::radians(10.0f))    &&    !(glm::angle(newOrientation,-m_Up) <= glm::radians(10.0f)))    {
      m_Orientation = newOrientation;
    }
      
    m_Orientation = glm::rotate(m_Orientation, glm::radians(-m_RotY),m_Up);
        
		glfwSetCursorPos(m_Window.handle(), (m_Window.width() / 2), (m_Window.height() / 2));
        
      
   //update left/right orientation
    m_Orientation = glm::rotate(m_Orientation, glm::radians(-m_RotY),m_Up);

   //reset rotation values each frame
    m_RotY = m_RotX = m_RotZ = 0;
    
  }


  if(!m_CaptureMouse){
   //Create update buffer for orientation of Vertical change in orientation
    glm::vec3 newOrientation = glm::rotate(m_Orientation, glm::radians(-m_RotX), glm::normalize(glm::cross(m_Orientation, m_Up)));

   //Decide if it's legal or not 
    //basically, bounding the up and down rotations to 10 degrees from top and bottom
    if(   !(glm::angle(newOrientation,m_Up) <= glm::radians(10.0f))    &&    !(glm::angle(newOrientation,-m_Up) <= glm::radians(10.0f)))    {
      m_Orientation = newOrientation;
    }
      
   //Update left/right orientation
    m_Orientation = glm::rotate(m_Orientation, glm::radians(-m_RotY),m_Up);

   //Reset rotation values each frame
    m_RotY = m_RotX = m_RotZ = 0;
  }

}



//Currently updates movespeed relative to delta, resets view and projection, 
void sCamera::update(float delta){
  getInput();

 //»»» UPDATE VARIABLES «««
  //how fast the camera moves
  float speed = m_MoveSpeed* delta;
        
 //»»» MATRICES «««
  //reset model and view
  m_View = glm::mat4(1.f);
  m_Proj = glm::mat4(1.f);

 //the actual view of the camera
  m_View = glm::lookAt(m_Position,m_Position + m_Orientation, m_Up);

 //perspective
  setPerspective(glm::radians(m_Fov), m_Aspect,m_Near,m_Far);

 //»»» UPDATE MAIN MATRIX «««
  //creates matrix to send off to models as a uniform
  m_CameraMatrix = m_Proj*m_View;
}

}//namespace shb