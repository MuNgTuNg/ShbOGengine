#include <sMetaApp.hpp>
#include <geometry/sShapes.hpp>
namespace shb{

class sDefaultApp : public sMetaApp{
    public:
    ~sDefaultApp() {
        if(!cleaned){
            cleanup();
        }
    }
    
    //Object ID system TODO
    sDefaultApp(){
        objects.push_back(new sPyramid{-4.f,0.f,-10.f});
        objects.push_back(new sIcosohedron{4.f,0.f,-10.f});
        objects.push_back(new sFloor{0.f,-5.f,10.f});
        objects[objects.size()-1]->setScale(20.f);
    }

    void getInput() {}
    void run() override{}

    void update(){}

    void update(sCamera& camera, double delta) override {
        //PYRAMIDS
        for(int i = 0; i < objects.size(); ++i){
          objects[i]->update(camera,delta);
          objects[i]->draw();
        }
    }

    void cleanup() override {
        for(int i = 0; i < objects.size(); ++i){
           delete objects[i];
        }
        cleaned = true;
    }

    bool cleaned = false;

};


}//namespace shb