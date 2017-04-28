#include "graphics/window.h"
#include "input/input_manager.h"
#include <iostream>

using namespace BS;

void mCb(InputManager* window, int button, int action, int mods)
{
    std::cout << "mCb triggered" << std::endl;
    if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        if(window->getWindow()->getWindowMode() == WindowMode::DEFAULT)
        {
            std::cout << "setting fullscreen" << std::endl;
            window->getWindow()->setWindowMode(WindowMode::FULLSCREEN);
        }
        else
        {
            window->getWindow()->setWindowMode(WindowMode::DEFAULT);
            std::cout << "setting default" << std::endl;
        }
    }
}

void cCb(InputManager* window, int button, int state, int action)
{
    std::cout << "cCb triggered" << std::endl;
}

void cursorPosMsg(InputManager* input, double xpos, double ypos)
{
    std::cout << "Cursor at x: " << xpos << ", y: " << ypos << std::endl;
}

int main(int argc, char *argv[])
{
    Window* window = new Window("Dreyri", 400, 400, WindowMode::DEFAULT);
    InputManager* input = window->getInputManager();
    
    //input->registerCallback(cb);
    //input->registerCallback(ccb);

    //input->registerCallback(cpcb);

    using namespace std::placeholders;

    auto cb = std::bind(mCb, input, _1, _2, _3);
    input->getMouseButtonSignal().connect(cb);

    auto ccb = std::bind(cCb, input, _1, _2, _3);
    input->getMouseButtonSignal().connect(ccb);

    auto cursorPos = std::bind(cursorPosMsg, input, _1, _2);
    auto connectionCursor = input->getCursorPosSignal().connect(cursorPos);
    connectionCursor->setTimeout(2000);

    //bool pressed = false;

    while(true)
    {

        window->swapBuffers();
        input->pollEvents();

        /*
        if(input->getMouseButton(*window, MouseButton::Left) == MouseButtonState::Press)
        {
            std::cout << "mousepress detected" << std::endl;
            //only update if this is the first press
            if(!pressed)
            {
                WindowMode curMode = window->getWindowMode();
                if(curMode == WindowMode::DEFAULT)
                    window->setWindowMode(WindowMode::FULLSCREEN);
                else
                    window->setWindowMode(WindowMode::DEFAULT);
            }
            pressed = true;
        }
        */

        /*
        else
            pressed = false;
        */
    }

    delete window;

    return 0;
}
