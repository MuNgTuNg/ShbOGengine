#include <sMetaApp.hpp>
#include <geometry/sShapes.hpp>
namespace shb{

class sRandomPyramids : public sMetaApp{
    public:
    ~sRandomPyramids() {
        if(!cleaned){
            cleanup();
        }
    }



    sRandomPyramids(){
        //how many objects to randomly generate
        int maxPyramids = 5000;
       
        //bounds of random number generation for position of pyramids
        float xLO = -10.f;
        float xHI = 10.f;
        float yLO = -10.f;
        float yHI = 10.f;
        float zLO = -20.f;
        float zHI = -.2f;
      
        //generates random numbers for 1000 objects x and y coordinates and loads them in before the main loop starts
        while(objects.size() < maxPyramids){
        float x = xLO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(xHI-xLO)));
        float y = yLO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(xHI-xLO)));
        float z = zLO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(zHI-zLO)));
        
        //sPyramid{(float)x,(float)y,(float)z};
        objects.push_back(new sPyramid{(float)x,(float)y,(float)z});
        }
        while(objects.size() < maxPyramids){
        float x = xLO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(xHI-xLO)));
        float y = yLO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(xHI-xLO)));
        float z = zLO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(zHI-zLO)));
        objects.push_back(new sIcosohedron{(float)x,(float)y,(float)z});
        }
    
    }
    
    void getInput() {}
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