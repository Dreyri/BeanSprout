#include "graphics/window.h"
#include "input/input_manager.h"

#include <iostream>

using namespace BS;

int main(void)
{
    Window* w = new Window();

    bool close = false;

    auto lambdaClose = [&]()
    {
        close = true;
        std::cout << "Close requested" << std::endl;
    };

    auto lambdaPos = [](double xpos, double ypos)
    {
        std::cout << "Window at x: " << xpos << ", y: " << ypos << std::endl;
    };

    auto lambdaMouseButton = [&](int button, int action, int state)
    {
        if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
        {
            auto mousePos = w->getInputManager()->getCursorPosition();
            std::cout << "Left Mouse button pressed at x: " << mousePos.x << ", y: " << mousePos.y << std::endl;
        }
    };

    auto lambdaSize = [](int width, int height)
    {
        std::cout << "Window resized, width: " << width << ", height: " << height << std::endl;
    };

    w->getInputManager()->getCloseSignal().connect(lambdaClose);
    w->getInputManager()->getPosSignal().connect(lambdaPos)->setTimeout(500);
    w->getInputManager()->getMouseButtonSignal().connect(lambdaMouseButton);
    w->getInputManager()->getSizeSignal().connect(lambdaSize);

    while(!close)
    {
        w->getInputManager()->pollEvents();
        w->swapBuffers();
    }

    delete w;

    return 0;
}
