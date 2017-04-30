#include "application.h"

namespace BS
{
Application::Application()
{
    if(!glfwInit())
    {
        std::cout << "E: failed to initialize GLFW!" << std::endl;
        glfwTerminate();
        exit(-1);
    }

    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

    mWindow = new Window();

}

Application::~Application()
{
    delete mWindow;
    glfwTerminate();
}
}
