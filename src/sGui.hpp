#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <sWindow.hpp>


#include <string>

namespace shb{

//once different functionalities emerge from this GUI class i can have polymorphic 
//derived classes that serve different purposes (like sGUI* moniter = new heartMoniter(); or sGUI* display = new debugDisplay();)


class sGUI{
 public:
    sGUI(sWindow& window); //options for creation, probably use an enum
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
 private:
   sWindow& m_Window;


};


class DefaultGUI : public sGUI{
 public:
  DefaultGUI(sWindow& window) : sGUI(window) {}

  void update() override {
    beginWindow("Default Window");
    endWindow();

  }
};

class TinkeringWindow : public sGUI{
 public:
  TinkeringWindow(sWindow& window) : sGUI(window) {
  }
  void update() override { 
    beginWindow("Tinkering Window");
    float value = 444;
    ImGui::DragFloat("No value chosen",&value,0.01);
    ImGui::DragFloat("No value chosen", &value,0.01);
  };
  void update(float& scale, float& angle,float& x,float& y,float& z) {
    //imgui stuff
    beginWindow("Tinkering Window");
    ImGui::Text("Hello Hello Hello");
    ImGui::DragFloat("Rotation",&angle,0.01);
    ImGui::DragFloat("x",&x,0.01);
    ImGui::DragFloat("y",&y,0.01);
    ImGui::DragFloat("z",&z,0.01);
    ImGui::DragFloat("Scale",&scale,0.01);
    endWindow();

  }
};
}