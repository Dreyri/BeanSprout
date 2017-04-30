#ifndef SCENE_H
#define SCENE_H

#include "graphics/camera.h"
#include "graphics/viewport.h"
#include <vector>

namespace BS
{
class Scene
{
private:
    std::vector<std::shared_ptr<Viewport>> mViewports;
public:
    Scene();
    virtual ~Scene();

    //concerns: how am I going to manage input callbacks etc?
    //okay I will have the state manager call only the signals in the currently active scene
    void blockInput();
};
}

#endif // SCENE_H
