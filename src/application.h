#ifndef APPLICATION_H
#define APPLICATION_H

#include "graphics/window.h"
#include "graphics/statemanager.h"
#include "util/resourcemanager.h"

namespace BS
{
class Application
{
private:
    Window* mWindow;
    StateManager* mState;
    ResourceManager* mResources;
public:
    Application();
    ~Application();
};
}

#endif // APPLICATION_H
