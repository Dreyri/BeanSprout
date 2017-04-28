#ifndef SCENE_H
#define SCENE_H

namespace BS
{
class Scene
{
public:
    Scene();

    //concerns: how am I going to manage input callbacks etc?
    //okay I will have the state manager call only the signals in the currently active scene
    void blockInput();
};
}

#endif // SCENE_H
