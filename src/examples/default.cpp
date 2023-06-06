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

    sDefaultApp(){
        pyramids.push_back({-4.f,0.f,-10.f});
        icosohedrons.push_back({4.f,0.f,-10.f});
        quad.setScale(20.f);
    }
    
    void getInput() {}
    void run() override{}

    void update(){}

    void update(sCamera& camera, double delta) override {
        quad.update(camera, delta);
        quad.draw();

        //PYRAMIDS
        for(int i = 0; i < pyramids.size(); ++i){
          pyramids[i].update(camera,delta);
          pyramids[i].draw();
        }
    
    
       //ICOSOHEDRONS
       for(int i = 0; i < icosohedrons.size(); ++i){
         icosohedrons[i].update(camera,delta);
         icosohedrons[i].draw();
       }

    }

    void cleanup() override {
        for(int i = 0; i < pyramids.size(); ++i){
           pyramids[i].cleanup();
        }
        cleaned = true;
    }

    std::vector<sPyramid> pyramids{};
    std::vector<sIcosohedron> icosohedrons{};
    sFloor quad{0.f,-5.f,10.f};
    bool cleaned = false;

};


}//namespace shb