#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include "graphics/scene.h"
#include <stack>

namespace BS
{

class StateManager
{
private:
    std::stack<Scene*> mScenes;
public:
    StateManager();

    void push(Scene* scene);
    void pop();
    Scene* getCurrentScene();
};
}

#endif // STATEMANAGER_H
