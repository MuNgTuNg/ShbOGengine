#pragma once
#include <sCamera.hpp>
#include "geometry/sShapes.hpp"
namespace shb{

class sMetaApp{
    public:

    virtual void getInput(){
        printf("No app assigned\n");
    }
    virtual void run() {
        printf("No app assigned\n");
    };
    virtual void cleanup() {
        printf("No app assigned\n");
    };
    virtual void update(sCamera&, double delta) {
        printf("No app assigned\n");
    };
    virtual void update() {
        //printf("No app assigned\n");
    };

    //not ideal for cache coherency but cool for toy apps. More intensive programmes will override this
    std::vector<sShape*> objects{};
};


}//namespace shb