#include <sApp.hpp>
#include <glad.c>
#include <stb_image.h>
#include <stdio.h>
#include <random>
#include <chrono>

#include "examples/default.cpp"
#include "examples/mandel.cpp"
#include "examples/randomPyramids.cpp"


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




sApp::sApp(){
  m_MetaApp = new sDefaultApp();
  srand(time(0));
  initImGui(m_Window);
}

void sApp::changeApp(apps choice){
  delete m_MetaApp;

  switch(choice){
    case RANDOM_PYRAMIDS:
      m_MetaApp = new sRandomPyramids();
      break;
    case MANDEL:
      break;

    case JULIA:
      m_MetaApp = new sMandelApp(m_Camera,m_Window);
      break;
    
    case DEFAULT:
      m_MetaApp = new sDefaultApp();
      break;
    
    default:
      m_MetaApp = new sDefaultApp();
      break;
  }
  sMainGUI::listenApp(m_MetaApp);
}

void sApp::getInput(){
    m_MetaApp->getInput();

    if(glfwGetKey(m_Window.handle(),GLFW_KEY_Z) == GLFW_PRESS ){
      changeApp(JULIA);
    }
    if(glfwGetKey(m_Window.handle(),GLFW_KEY_I) == GLFW_PRESS ){
      changeApp(DEFAULT);
    }
    if(glfwGetKey(m_Window.handle(),GLFW_KEY_Y) == GLFW_PRESS ){
      changeApp(RANDOM_PYRAMIDS);
    }

    if(glfwGetKey(m_Window.handle(),GLFW_KEY_Q) == GLFW_PRESS || glfwWindowShouldClose(m_Window.handle())){
      m_Running = false;
    }
}


void sApp::run(){
  sMainGUI gui{m_MetaApp,m_Window}; //FIX
  
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
    m_Window.update(); //update window, keep viewport same size as screen
    getInput();
    
    //calculate delta
    m_CurrentFrameTime = glfwGetTime();       
    m_DeltaTime = m_CurrentFrameTime - m_PreviousFrameTime;
    m_PreviousFrameTime = m_CurrentFrameTime;         
    m_FrameTimeInMS = m_DeltaTime *1000;
    
    //update 3D coords
    m_Camera.update(m_DeltaTime);
    
    //update metaApp
    m_MetaApp->update(m_Camera,m_DeltaTime);
    
    // IMGUI demo window
    ImGui::ShowDemoWindow();
    
    //imgui 
    gui.update(m_Camera,m_DeltaTime);
    gui.render();
  
   
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