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

  srand(time(0));


//game objexts
  std::vector<sPyramid> pyramids{};

 
 //how many objects to randomly generate
  int maxPyramids = 1000;
 
 //bounds of random number generation for position of pyramids
  float xLO = -1000.f;
  float xHI = 1000.f;
  float yLO = -1000.f;
  float yHI = 1000.f;
  float zLO = -2000.f;
  float zHI = -.2f;

  //controls half the triangles scales
  float globalPyramidScale = 10.f;
 
 //changing z value of camera
  float z = 0.f;

   
  

  //»»» MAIN LOOP «««
  while (!glfwWindowShouldClose(m_Window.handle()))
  { 

  
  //generates random numbers for 1000 objects x and y coordinates and loads them in sequentially
    while(pyramids.size() < maxPyramids){
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

    //camera rotation matrix needs work, it is drunk
    m_Camera.update(m_DeltaTime);
   
    

   //manipulates pyramid objects
    for(int i = 0; i < pyramids.size(); ++i){
      pyramids[i].update(m_Camera,m_DeltaTime);
    }
  

  
   
   //imgui stuff
    tinkerWindow.update(m_Camera,
                        pyramids[1], 
                        m_DeltaTime,
                        globalPyramidScale
                        );

    tinkerWindow.render();


    

   //swap buffers
    glfwSwapBuffers(m_Window.handle()); 
   //poll events
    glfwPollEvents();           //have any window events happened? 
  }
 
  for(int i = 0; i < pyramids.size(); ++i){
      pyramids[i].cleanup();
  }

   
  //check for errors
  checkError(__FILE__,__LINE__);
   

}


sApp::~sApp(){
     
 //cleanup
  tinkerWindow.destroyGUI();
  m_Window.destroy();
  glfwTerminate();
}

}//namespace shb