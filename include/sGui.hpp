#pragma once
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <sMetaApp.hpp>
#include <sApp.hpp>
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
  ~sGUI() {}; 
  sGUI(const sGUI&) = delete;

  virtual void update() = 0;

 public:
   void initGUI();
   void beginWindow(const std::string& name);
   void render();
   void endWindow();

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
    endWindow();
  }

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
      if(ImGui::CollapsingHeader("Quad:floor")){
        //pos
        ImGui::SliderFloat((m_Object->m_Name  + " x").c_str(),&m_Object->m_X,-100,100);
        ImGui::SliderFloat((m_Object->m_Name + " y").c_str(),&m_Object->m_Y,-100,100);
        ImGui::SliderFloat((m_Object->m_Name + " z").c_str(),&m_Object->m_Z,-100,100);

        //rot
        ImGui::InputFloat((m_Object->m_Name  + " rotX").c_str(),&m_Object->m_RotAxisx,-100,100);
        ImGui::InputFloat((m_Object->m_Name + " rotY").c_str(),&m_Object->m_RotAxisy,-100,100);
        ImGui::InputFloat((m_Object->m_Name + " RotZ").c_str(),&m_Object->m_RotAxisz,-100,100);
        ImGui::InputFloat((m_Object->m_Name + " angle").c_str(),&m_Object->m_Angle,-100,100);
      }
    }
    endWindow();

  }

  sShape* m_Object = nullptr;

};


class sMainGUI : public sGUI{
  public: 
  static void listenApp(sMetaApp* app){
    appCtxt = app;
  }
  sMainGUI(sMetaApp* app,
           sWindow& window, 
           const std::string& title = "ShbOGengine") : /*appCtxt(app),*/
                                                       sGUI(window,title){
                                                        sMainGUI::appCtxt = app;
                                                       }
  
  void update() {}
  void update(sCamera& camera, double delta ){ 
    beginWindow(m_Title);

    ImGui::Text("Calling update");

    //camera(); TODO
    //objects();

     //CAMERA
    if(ImGui::CollapsingHeader("Camera")){
     
      ImGui::Text("MSPF: %fms", delta*1000);         
      ImGui::Text("FPS: %fms", 1/(delta));

    
      ImGui::Text("Press C to capture mouse");
      ImGui::Text("Press X to release mouse");

      ImGui::DragFloat("x",&camera.m_Position.x,camera.m_MoveSpeed);
      ImGui::DragFloat("y",&camera.m_Position.y,camera.m_MoveSpeed);
      ImGui::DragFloat("z",&camera.m_Position.z,camera.m_MoveSpeed);

      ImGui::DragFloat("FOV",&camera.m_Fov,camera.m_MoveSpeed);
      ImGui::DragFloat("Move Speed",&camera.m_MoveSpeed,0.4f);
      
      ImGui::Checkbox("Movement", &camera.m_KeyboardInput);    
   
    }
     
     //OBJECTS
    if(ImGui::CollapsingHeader("Objects")){
      if(!appCtxt){
        ImGui::Text("No App!");
        return;
      }
      if(appCtxt->objects.empty()  || appCtxt->objects[objIdx]==nullptr){
          ImGui::Text("No Objects!");
          return;
      }
      
      ImGui::Text(appCtxt->objects[objIdx]->m_Name.c_str());
      ImGui::SliderFloat("x",&appCtxt->objects[objIdx]->m_X,-100,100);
      ImGui::SliderFloat("y",&appCtxt->objects[objIdx]->m_Y,-100,100);
      ImGui::SliderFloat("z",&appCtxt->objects[objIdx]->m_Z,-100,100);

      //rot
      ImGui::InputFloat("rotX",&appCtxt->objects[objIdx]->m_RotAxisx,-100,100);
      ImGui::InputFloat("rotY",&appCtxt->objects[objIdx]->m_RotAxisy,-100,100);
      ImGui::InputFloat("RotZ",&appCtxt->objects[objIdx]->m_RotAxisz,-100,100);
      ImGui::InputFloat("angle",&appCtxt->objects[objIdx]->m_Angle,-100,100);
      
      std::string indexMsg = "Object Index: " + std::to_string(objIdx);
      ImGui::Text(indexMsg.c_str());


      if (ImGui::TreeNode("All Objects:"))
      {
        // Using the generic BeginListBox() API, you have full control over how to display the combo contents.
        // (your selection data could be an index, a pointer to the object, an id for the object, a flag intrusively
        // stored in the object itself, etc.)
        static int item_current_idx = 0; // Here we store our selection data as an index.
    
           // Custom size: use all width, 5 items tall
           if (ImGui::BeginListBox("All Objects", ImVec2(-FLT_MIN, 5 * ImGui::GetTextLineHeightWithSpacing())))
           {
               for (int n = 0; n < appCtxt->objects.size(); n++)
               {
                   const bool is_selected = (item_current_idx == n);
                   if (ImGui::Selectable(appCtxt->objects[n]->m_Name.c_str(), is_selected))
                       objIdx = n;
   
                   // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                   if (is_selected)
                       ImGui::SetItemDefaultFocus();
               }
               ImGui::EndListBox();
           }
   
           ImGui::TreePop();
         }

      }//end of collapsing header
      
      
    

    endWindow();

  }//update
  
  void camera();
  void objects();
 
  int objIdx = 0;
  static sMetaApp* appCtxt;
  
  ~sMainGUI(){
    appCtxt = nullptr;
  }
};

}//namespace shhb

