#include <sApp.hpp>
#include <glad.c>
#include <stb_image.h>
#include <stdio.h>
#include <random>
#include <chrono>


namespace shb{

/*
TODO:: 
    1. Fix whatever is going on with shader handles that's making the error messages happen
    2. Make Shape base class responsible for cleaning itself up, add "textured shape" "non textured shape" etc
    3. Rename sShapes class to sGameObject and make it an abstract base class (maybe)
    4. Make sGUI an observer of sGameObjects 
    5. Sort the stupid debugging folder into appropriate src/include folders
    6. Add meshes
    7. 
    8. Finally have fun

*/

/*
⋯⋯⋯⋯⋯⊱⊰⋯⋯⋯⋯⋯⋯⋯⋯⋯⋯⊱⊰⋯⋯⋯⋯⋯⋯⋯⋯⋯⋯⊱⊰⋯⋯⋯⋯⋯⋯⋯⋯⋯⋯⊱⊰⋯⋯⋯⋯⋯⋯⋯⋯⋯⋯⊱⊰⋯⋯⋯⋯⋯⋯⋯⋯⋯⋯⊱⊰⋯⋯⋯⋯⋯⋯⋯⋯⋯⋯⊱⊰⋯⋯⋯⋯⋯⋯⋯⋯⋯⋯⊱⊰⋯⋯⋯⋯⋯
          »»»SETUP SCENE«««
            Sets up game objects
⋯⋯⋯⋯⋯⊱⊰⋯⋯⋯⋯⋯⋯⋯⋯⋯⋯⊱⊰⋯⋯⋯⋯⋯⋯⋯⋯⋯⋯⊱⊰⋯⋯⋯⋯⋯⋯⋯⋯⋯⋯⊱⊰⋯⋯⋯⋯⋯⋯⋯⋯⋯⋯⊱⊰⋯⋯⋯⋯⋯⋯⋯⋯⋯⋯⊱⊰⋯⋯⋯⋯⋯⋯⋯⋯⋯⋯⊱⊰⋯⋯⋯⋯⋯⋯⋯⋯⋯⋯⊱⊰⋯⋯⋯⋯⋯
*/
sApp::sApp(){
  //seeds random number generator
  srand(time(0));

  mandel.listenWindow(&m_Window);
  mandel.listenCamera(&m_Camera);

  //how many objects to randomly generate
  int maxPyramids = 300;
 
  //bounds of random number generation for position of pyramids
  float xLO = -1.f;
  float xHI = 10.f;
  float yLO = -10.f;
  float yHI = 10.f;
  float zLO = -20.f;
  float zHI = -.2f;

  int i = 0;
  //generates random numbers for 1000 objects x and y coordinates and loads them in before the main loop starts
  while(pyramids.size() < maxPyramids){
  float x = xLO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(xHI-xLO)));
  float y = yLO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(xHI-xLO)));
  float z = zLO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(zHI-zLO)));

  pyramids.push_back({(float)-i,(float)i,(float)i-5});
  --i;
  }
  int j = 0;
  while(icosohedrons.size() < maxPyramids){
  float x = xLO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(xHI-xLO)));
  float y = yLO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(xHI-xLO)));
  float z = zLO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(zHI-zLO)));
  j--;//manipulates pyramid objects
  icosohedrons.push_back({(float)j,(float)-j,(float)j-5});
  }

  //TODO:: make this quad a floor
  //quad.setScale(100.f);
}

void sApp::getInput(){

    if(glfwGetKey(m_Window.handle(),GLFW_KEY_W) == GLFW_PRESS || glfwGetKey(m_Window.handle(),GLFW_KEY_SPACE) == GLFW_PRESS){
        if(mandelbrotStart){ //TODO:: implement this in imgui so that i can choose from a gui
          mandel.offsetY += m_Camera.m_MoveSpeed;
        }
        if(juliaStart){
          julia.offsetY += m_Camera.m_MoveSpeed;
        }
    }
    
    if(glfwGetKey(m_Window.handle(),GLFW_KEY_A) == GLFW_PRESS){
      if(juliaStart){
        julia.offsetX -= m_Camera.m_MoveSpeed;
      }
      if(mandelbrotStart){
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

void sApp::run(){
  /*
  ⋯⋯⋯⋯⋯⊱⊰⋯⋯⋯⋯⋯⋯⋯⋯⋯⋯⊱⊰⋯⋯⋯⋯⋯⋯⋯⋯⋯⋯⊱⊰⋯⋯⋯⋯⋯⋯⋯⋯⋯⋯⊱⊰⋯⋯⋯⋯⋯⋯⋯⋯⋯⋯⊱⊰⋯⋯⋯⋯⋯⋯⋯⋯⋯⋯⊱⊰⋯⋯⋯⋯⋯⋯⋯⋯⋯⋯⊱⊰⋯⋯⋯⋯⋯⋯⋯⋯⋯⋯⊱⊰⋯⋯⋯⋯⋯
                                   
  █▀▄▀█ ▄▀█ █ █▄░█   █░░ █▀█ █▀█ █▀█
  █░▀░█ █▀█ █ █░▀█   █▄▄ █▄█ █▄█ █▀▀
      where the real business is
  ⋯⋯⋯⋯⋯⊱⊰⋯⋯⋯⋯⋯⋯⋯⋯⋯⋯⊱⊰⋯⋯⋯⋯⋯⋯⋯⋯⋯⋯⊱⊰⋯⋯⋯⋯⋯⋯⋯⋯⋯⋯⊱⊰⋯⋯⋯⋯⋯⋯⋯⋯⋯⋯⊱⊰⋯⋯⋯⋯⋯⋯⋯⋯⋯⋯⊱⊰⋯⋯⋯⋯⋯⋯⋯⋯⋯⋯⊱⊰⋯⋯⋯⋯⋯⋯⋯⋯⋯⋯⊱⊰⋯⋯⋯⋯⋯
  */



  //»»» MAIN LOOP «««
  while (!glfwWindowShouldClose(m_Window.handle()))
  { 

    //update window, keep viewport same size as screen
    m_Window.update();
    cameraWindow.startFrame();
    getInput();

    //»»» DELTA TIME «««
    m_CurrentFrameTime = glfwGetTime();       //get current time
    m_DeltaTime = m_CurrentFrameTime - m_PreviousFrameTime;//get amount of time elapsed since last frame
    m_PreviousFrameTime = m_CurrentFrameTime;               //set this frames time for next iteration comparison
    m_FrameTimeInMS = m_DeltaTime *1000;


    //»»» GLOBAL 3D «««
    m_Camera.update(m_DeltaTime);


    //PYRAMIDS
    for(int i = 0; i < pyramids.size(); ++i){
      pyramids[i].update(m_Camera,m_DeltaTime);
      pyramids[i].draw();
    }
    
    //ICOSOHEDRONS
    for(int i = 0; i < icosohedrons.size(); ++i){
      icosohedrons[i].update(m_Camera,m_DeltaTime);
      icosohedrons[i].draw();
    }

    // mandel.update(m_Camera,m_DeltaTime);
    // mandel.draw();
    julia.update(m_Camera,m_DeltaTime);
    julia.draw();

    //controls half the triangles scales
    float globalPyramidScale = 10.f;

 
    //imgui stuff
    cameraWindow.update( &m_Camera, m_DeltaTime);


    cameraWindow.render();

    //if Q is pressed, break out of the main loop and quit the application
    if(glfwGetKey(m_Window.handle(),GLFW_KEY_Q) == GLFW_PRESS){
      break;
    }
    //swap buffers
    glfwSwapBuffers(m_Window.handle()); 
    //poll events
    glfwPollEvents();           //have any window events happened? 
  }
 
  //check for errors
  if(DEBUG){
      checkError(__FILE__,__LINE__,"Main Loop Finish:");
  }
}




void sApp::cleanup(){
  //delete all pyramids
  for(int i = 0; i < pyramids.size(); ++i){
      pyramids[i].cleanup();
  }
 
  cameraWindow.destroyGUI();
  m_Window.destroy();

  glfwTerminate();
}


sApp::~sApp(){
  cleanup();
}


}//namespace shb