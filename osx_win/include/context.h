#ifndef __CONTEXT__
#define __CONTEXT__
#include "hw1.h"
#include "hw2.h"


#include "hw1.h"


using namespace imageSpace;


class Context{
    //Maintain state if needed
    imageSpace::CameraImage<int> i = CameraImage<int>(1000,480);

public:

    int height = 480; // for example
    int width = 640; // for example
    bool use_average = false;
    bool use_invert = false;
    bool use_flip = false;

};

#endif
