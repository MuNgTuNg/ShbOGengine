#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <sWindow.hpp>
#include <sCamera.hpp>
#include <geometry/sShapes.hpp>

#include <string>

namespace shb{

//once different functionalities emerge from this GUI class i can have polymorphic 
//derived classes that serve different purposes (like sGUI* moniter = new heartMoniter(); or sGUI* display = new debugDisplay();)
bool initImGui(sWindow& m_Window);


class sGUI{
 public:
    sGUI(sWindow& window, const std::string& title);
    ~sGUI(); 
    sGUI(const sGUI&) = delete;

    virtual void update() = 0;

 public:
   void initGUI();
   void startFrame();
   void endWindow();
   void destroyGUI();
   void render();
   void beginWindow(const std::string& name);

   std::string m_Title;
 private:
   sWindow& m_Window;

};


class sCameraGUI : public sGUI{
 public:
  float x = 0.f,y = 0.f,z =0.f;

  sCameraGUI(sWindow& window, const std::string& title) : sGUI(window, title) {}

  void update() override { 
    beginWindow(m_Title);
    float value = 444;
    ImGui::DragFloat("No value chosen",&value,0.01);
    ImGui::DragFloat("No value chosen", &value,0.01);
  };

  double timer = 0;
  
  void update(sCamera* camera, double& delta){ 
    //delta in ms
    beginWindow(m_Title);

    ImGui::Text("MSPF: %fms", delta*1000);         //todo make this legible at runtime
    ImGui::Text("FPS: %fms", 1/(delta));

  
    ImGui::Text("Press C to capture mouse");
    ImGui::Text("Press X to release mouse");

    ImGui::DragFloat("x",&camera->m_Position.x,camera->m_MoveSpeed);
    ImGui::DragFloat("y",&camera->m_Position.y,camera->m_MoveSpeed);
    ImGui::DragFloat("z",&camera->m_Position.z,camera->m_MoveSpeed);

    ImGui::DragFloat("FOV",&camera->m_Fov,camera->m_MoveSpeed);
    ImGui::DragFloat("Move Speed",&camera->m_MoveSpeed,0.4f);
    
    ImGui::Checkbox("Movement", &camera->m_KeyboardInput);     
    endWindow();
  }
};

class sObjectGUI : public sGUI{
  public:
  sObjectGUI(sWindow& window, const std::string& title) : sGUI(window,title){}
  
  void selectObject(sShape* object){
    m_Object = object;
  }

  void update() override {
    beginWindow(m_Title);
    if(m_Object){
      ImGui::SliderFloat((m_Object->m_Name  + " x").c_str(),&m_Object->m_X,-100,100);
      ImGui::SliderFloat((m_Object->m_Name + " y").c_str(),&m_Object->m_Y,-100,100);
      ImGui::SliderFloat((m_Object->m_Name + " z").c_str(),&m_Object->m_Z,-100,100);
    }
    endWindow();

  }

  sShape* m_Object = nullptr;

};
}//namespace shhb

