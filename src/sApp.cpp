#include <sApp.hpp>
#include <glad.c>
#include <stb_image.h>

#include <random>
#include <chrono>


namespace shb{


/*
TODO:: 
    1. Add cool logos from my windows partition to the project
    2. Comb through the rest of this and clean up a little
    3. change the pyramid to an icosohedron 
    4. Fix whatever is going on with shader handles that's making the error messages happen
    5. Add necessary functions to the sShape class 
    6. Rename sShapes class to sGameObject and make it an abstract base class
    7. Make sGUI an observer of sGameObjects 
    8. Finally have fun

*/


sApp::sApp(){}


void sApp::run(){
//»»»WINDOW«««
  //creates window and initialises glad on current context by default
  m_Window.initWindow();

//»»» GUI «««
  tinkerWindow.initGUI();


//game objexts
std::vector<sPyramid> pyramids{};


for(int i = 0; i < 1000; ++i){
 
}


  srand(time(0));


  //»»» 3D «««
  float fov = 90.f;

  int numOfObjects = 0;
  float xLO = -10.f;
  float xHI = 10.f;
  float yLO = -10.f;
  float yHI = 10.f;
  float zLO = -10.f;
  float zHI = -.5f;

  float globalX = 0.f; float globalY = 0.f; float globalZ=-2.f;
 
  //»»» MAIN LOOP «««
  while (!glfwWindowShouldClose(m_Window.handle()))
  { 

    //generates random numbers for 1000 objects x and y coordinates and loads them in sequentially
    if(pyramids.size() < 1000){
    float x = xLO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(xHI-xLO)));
    float y = yLO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(xHI-xLO)));
    float z = zLO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(zHI-zLO)));

    pyramids.push_back({x,y,z});
    pyramids.back().init();
    }

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
    view = glm::translate(view,glm::vec3(globalX,globalY,globalZ));
    
    for(int i = 0; i < pyramids.size(); ++i){
      pyramids[i].update(model,view,proj,m_DeltaTime);
    }
   
   //imgui stuff
    //tinkerWindow could take an object as parameters instead of loads of variables
    //init imgui
    
    tinkerWindow.update(pyramids[1].scale,pyramids[1].angle,globalX,globalY,globalZ, fov, m_FrameTimeInMS, pyramids[1].rotAxisx, pyramids[1].rotAxisy, pyramids[1].rotAxisz);
    tinkerWindow.render();


    

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