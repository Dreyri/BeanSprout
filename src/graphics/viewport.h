#ifndef VIEWPORT_H
#define VIEWPORT_H

#include "graphics/camera.h"
#include <functional>

namespace BS
{

class Viewport
{
private:
    int mWidth, mHeight;

    std::shared_ptr<Camera> mCamera;
public:
    Viewport(int width, int height);
};

}

#endif // VIEWPORT_H
