#include <sApp.hpp>
#include <glad.c>
#include <stb_image.h>


namespace shb{





sApp::sApp(){}


void sApp::run(){
//»»»WINDOW«««
  //creates window and initialises glad on current context by default
  m_Window.initWindow();

//»»» GUI «««
  tinkerWindow.initGUI();


//game objexts
  sPyramid pyramid;  //todo add vertex and index buffer objects to sShape class
  pyramid.init();



  //»»» 3D «««
  float x = 0.f;
  float y = 0.f;
  float z = -2.f;

  float fov = 45.f;


 
  //»»» MAIN LOOP «««
  while (!glfwWindowShouldClose(m_Window.handle()))
  { 

   //»»» DELTA TIME «««
    m_CurrentFrameTime = glfwGetTime();       //get current time
    m_DeltaTime = m_CurrentFrameTime - m_PreviousFrameTime;//get amount of time elapsed since last frame
    m_PreviousFrameTime = m_CurrentFrameTime;               //set this frames time for next iteration comparison
    
    m_FrameTimeInMS = m_DeltaTime *1000;

   

   //update window, keep viewport same size as screen
    m_Window.update();
   //init imgui
    tinkerWindow.startFrame();
    


   //»»» GLOBAL 3D «««
    glm::mat4 model = glm::mat4(1.f); 
    glm::mat4 view = glm::mat4(1.f); 
    glm::mat4 proj = glm::mat4(1.f); 

    view = glm::translate(view,glm::vec3(x,y,z));
    proj = glm::perspective(glm::radians(fov), (float)m_Window.width()/m_Window.height(),0.1f,100.f);
  
    pyramid.update(model,view,proj,m_DeltaTime);

   //imgui stuff
    //tinkerWindow could take an object as parameters instead of loads of variables
    tinkerWindow.update(pyramid.scale,pyramid.angle,x,y,z, fov , m_FrameTimeInMS, pyramid.rotAxisx, pyramid.rotAxisy, pyramid.rotAxisz);
    tinkerWindow.render();

    //checkError(__FILE__,__LINE__);
   //swap buffers
    glfwSwapBuffers(m_Window.handle()); 
   //poll events
    glfwPollEvents();           //have any window events happened? 
  }
 

  //check for errors
  checkError(__FILE__,__LINE__);
   

  pyramid.cleanup();

}


sApp::~sApp(){
     
 //cleanup
  tinkerWindow.destroyGUI();
  m_Window.destroy();
  glfwTerminate();
}

}//namespace shb