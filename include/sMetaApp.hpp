#pragma once
#include <sCamera.hpp>

namespace shb{

class sMetaApp{
    sMetaApp(sCamera& camera, double delta);
    virtual ~sMetaApp() = 0;
    virtual void run() = 0;
    virtual void cleanup() = 0;
};


}//namespace shb