#include <sApp.hpp>
#include <glad.c>
#include <stb_image.h>
#include <stdio.h>
#include <random>
#include <chrono>

#include "examples/default.cpp"
#include "examples/mandel.cpp"


namespace shb{

/*
TODO:: 
    1. Fix whatever is going on with shader handles that's making the error messages happen
    2. Make Shape base class responsible for cleaning itself up, add "textured shape" "non textured shape" etc
    3. Rename sShapes class to sGameObject and make it an abstract base class (maybe)
    4. Make sGUI an observer of sGameObjects 
    5. Sort the stupid debugging folder into appropriate src/include folders
    6. Add meshes
    7. make the shapes into point lights
    8. texture the floor
    9. Finally have fun

*/

/*
⋯⋯⋯⋯⋯⊱⊰⋯⋯⋯⋯⋯⋯⋯⋯⋯⋯⊱⊰⋯⋯⋯⋯⋯⋯⋯⋯⋯⋯⊱⊰⋯⋯⋯⋯⋯⋯⋯⋯⋯⋯⊱⊰⋯⋯⋯⋯⋯⋯⋯⋯⋯⋯⊱⊰⋯⋯⋯⋯⋯⋯⋯⋯⋯⋯⊱⊰⋯⋯⋯⋯⋯⋯⋯⋯⋯⋯⊱⊰⋯⋯⋯⋯⋯⋯⋯⋯⋯⋯⊱⊰⋯⋯⋯⋯⋯
          »»»SETUP SCENE«««
            Sets up game objects
⋯⋯⋯⋯⋯⊱⊰⋯⋯⋯⋯⋯⋯⋯⋯⋯⋯⊱⊰⋯⋯⋯⋯⋯⋯⋯⋯⋯⋯⊱⊰⋯⋯⋯⋯⋯⋯⋯⋯⋯⋯⊱⊰⋯⋯⋯⋯⋯⋯⋯⋯⋯⋯⊱⊰⋯⋯⋯⋯⋯⋯⋯⋯⋯⋯⊱⊰⋯⋯⋯⋯⋯⋯⋯⋯⋯⋯⊱⊰⋯⋯⋯⋯⋯⋯⋯⋯⋯⋯⊱⊰⋯⋯⋯⋯⋯
*/
sApp::sApp(){
  //seeds random number generator
  m_MetaApp = new sDefaultApp();
  srand(time(0));
  initImGui(m_Window);


  //how many objects to randomly generate
  int maxPyramids = 10;
 
  //bounds of random number generation for position of pyramids
  float xLO = -1.f;
  float xHI = 10.f;
  float yLO = -10.f;
  float yHI = 10.f;
  float zLO = -20.f;
  float zHI = -.2f;

  // int i = 0;
  // //generates random numbers for 1000 objects x and y coordinates and loads them in before the main loop starts
  // while(pyramids.size() < maxPyramids){
  // float x = xLO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(xHI-xLO)));
  // float y = yLO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(xHI-xLO)));
  // float z = zLO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(zHI-zLO)));

  // pyramids.push_back({(float)-i,(float)i,(float)i-5});
  // --i;
  // }
  // int j = 0;
  // while(icosohedrons.size() < maxPyramids){
  // float x = xLO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(xHI-xLO)));
  // float y = yLO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(xHI-xLO)));
  // float z = zLO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(zHI-zLO)));
  // j--;//manipulates pyramid objects
  // icosohedrons.push_back({(float)j,(float)-j,(float)j-5});
  // }

  //TODO:: create all object vector
  //allObjects.push_back(pyramids);
  //allObjects.push_back(icosohedrons);
  
}

void sApp::changeApp(sMetaApp* app){
    delete m_MetaApp;
    m_MetaApp = app;
}

void sApp::getInput(){

    m_MetaApp->getInput();

    if(glfwGetKey(m_Window.handle(),GLFW_KEY_Z) == GLFW_PRESS ){
      changeApp(new sMandelApp(m_Camera,m_Window));
    }
    if(glfwGetKey(m_Window.handle(),GLFW_KEY_X) == GLFW_PRESS ){
      changeApp(new sDefaultApp());
    }

    //if Q is pressed, break out of the main loop and quit the application
    if(glfwGetKey(m_Window.handle(),GLFW_KEY_Q) == GLFW_PRESS || glfwWindowShouldClose(m_Window.handle())){
      m_Running = false;
    }
}


void sApp::run(){
  /*
  ⋯⋯⋯⋯⋯⊱⊰⋯⋯⋯⋯⋯⋯⋯⋯⋯⋯⊱⊰⋯⋯⋯⋯⋯⋯⋯⋯⋯⋯⊱⊰⋯⋯⋯⋯⋯⋯⋯⋯⋯⋯⊱⊰⋯⋯⋯⋯⋯⋯⋯⋯⋯⋯⊱⊰⋯⋯⋯⋯⋯⋯⋯⋯⋯⋯⊱⊰⋯⋯⋯⋯⋯⋯⋯⋯⋯⋯⊱⊰⋯⋯⋯⋯⋯⋯⋯⋯⋯⋯⊱⊰⋯⋯⋯⋯⋯
                                   
  █▀▄▀█ ▄▀█ █ █▄░█   █░░ █▀█ █▀█ █▀█
  █░▀░█ █▀█ █ █░▀█   █▄▄ █▄█ █▄█ █▀▀
      where the real business is
  ⋯⋯⋯⋯⋯⊱⊰⋯⋯⋯⋯⋯⋯⋯⋯⋯⋯⊱⊰⋯⋯⋯⋯⋯⋯⋯⋯⋯⋯⊱⊰⋯⋯⋯⋯⋯⋯⋯⋯⋯⋯⊱⊰⋯⋯⋯⋯⋯⋯⋯⋯⋯⋯⊱⊰⋯⋯⋯⋯⋯⋯⋯⋯⋯⋯⊱⊰⋯⋯⋯⋯⋯⋯⋯⋯⋯⋯⊱⊰⋯⋯⋯⋯⋯⋯⋯⋯⋯⋯⊱⊰⋯⋯⋯⋯⋯
  */
  //»»» MAIN LOOP «««
  while (m_Running)
  { 
    startImGuiFrame();
    //update window, keep viewport same size as screen
    m_Window.update();
    getInput();

    //»»» DELTA TIME «««
    m_CurrentFrameTime = glfwGetTime();       //get current time
    m_DeltaTime = m_CurrentFrameTime - m_PreviousFrameTime;//get amount of time elapsed since last frame
    m_PreviousFrameTime = m_CurrentFrameTime;               //set this frames time for next iteration comparison
    m_FrameTimeInMS = m_DeltaTime *1000;
    
    //»»» GLOBAL 3D «««
    m_Camera.update(m_DeltaTime);

    m_MetaApp->update(m_Camera,m_DeltaTime);
    
    
     // IMGUI demo window
    ImGui::ShowDemoWindow();

   
    //imgui stuff
    cameraWindow.update( &m_Camera, m_DeltaTime);
    objectsWindow.update();
    cameraWindow.render();

   
    glfwSwapBuffers(m_Window.handle()); 
    glfwPollEvents();          
  }
 
  //check for errors
  if(DEBUG){
      checkError(__FILE__,__LINE__,"Main Loop Finish:");
  }
}




void sApp::cleanup(){
  m_MetaApp->cleanup();
  destroyImGui();
  m_Window.destroy();
  glfwTerminate();
}


sApp::~sApp(){
  cleanup();
}


}//namespace shb