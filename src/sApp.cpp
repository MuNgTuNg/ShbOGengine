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
std::vector<sPyramid> pyramids{};
for(int i = 0; i < 100; ++i){
  float j = i * 0.1;
  pyramids.push_back({j-1,0,-2.f});
  pyramids[i].init();
}



  

  //»»» 3D «««
  float fov = 90.f;

 
  //»»» MAIN LOOP «««
  while (!glfwWindowShouldClose(m_Window.handle()))
  { 

   //update window, keep viewport same size as screen
    m_Window.update();
    tinkerWindow.startFrame();
   

   //»»» DELTA TIME «««
    m_CurrentFrameTime = glfwGetTime();       //get current time
    m_DeltaTime = m_CurrentFrameTime - m_PreviousFrameTime;//get amount of time elapsed since last frame
    m_PreviousFrameTime = m_CurrentFrameTime;               //set this frames time for next iteration comparison
    
    m_FrameTimeInMS = m_DeltaTime *1000;

   

    //»»» GLOBAL 3D «««
    glm::mat4 model = glm::mat4(1.f); 
    glm::mat4 view = glm::mat4(1.f); 
    glm::mat4 proj = glm::mat4(1.f); 

    proj = glm::perspective(glm::radians(fov), (float)m_Window.width()/m_Window.height(),0.1f,100.f);

    for(int i = 0; i < pyramids.size(); ++i){
      pyramids[i].update(model,view,proj,m_DeltaTime);
    }
   
   //imgui stuff
    //tinkerWindow could take an object as parameters instead of loads of variables
    //init imgui
    
    tinkerWindow.update(pyramids[1].scale,pyramids[1].angle,pyramids[1].m_X,pyramids[1].m_Y,pyramids[1].m_Z, fov, m_FrameTimeInMS, pyramids[1].rotAxisx, pyramids[1].rotAxisy, pyramids[1].rotAxisz);
    tinkerWindow.render();


    

    //checkError(__FILE__,__LINE__);
   //swap buffers
    glfwSwapBuffers(m_Window.handle()); 
   //poll events
    glfwPollEvents();           //have any window events happened? 
  }
 

  //check for errors
  checkError(__FILE__,__LINE__);
   

  //pyra1.cleanup();

}


sApp::~sApp(){
     
 //cleanup
  tinkerWindow.destroyGUI();
  m_Window.destroy();
  glfwTerminate();
}

}//namespace shb