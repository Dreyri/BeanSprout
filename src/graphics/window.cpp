#include "window.h"
#include "input/input_manager.h"

#include "signal/signal.h"

#include <iostream>

namespace BS
{


Window::Window(const std::string& name, int width, int height, WindowMode mode, int refreshrate)
    : mName(name), mWindowMode(mode), mInput(nullptr), mRefreshRate(refreshrate)
{
    if(!glfwInit())
    {
        glfwTerminate();
        std::cout << "Failed to init GLFW!" << std::endl;
        return;
    }

    GLFWmonitor* monitor = nullptr;

    if(mWindowMode == WindowMode::FULLSCREEN)
    {
        monitor = glfwGetPrimaryMonitor();
    }
    else if(mWindowMode == WindowMode::BORDERLESS_FULLSCREEN)
    {
        std::cout << "Borderless Fullscreen is not yet implemented!" << std::endl;
    }

    //if we have obtained a monitor we're fullscreen
    if(!monitor && mWindowMode == WindowMode::FULLSCREEN)
        std::cout << "Could not obtain monitor for fullscreen" << std::endl;

    mWindow = glfwCreateWindow(width, height, mName.c_str(), monitor, NULL);
    if(!mWindow)
    {
        glfwTerminate();
        std::cout << "Failed to create GLFW window!" << std::endl;
        return;
    }

    glfwSetWindowUserPointer(mWindow, this);

    //register things with the input manager
    mInput = new InputManager(this);

    //to set the refresh rate
    setRefreshRate(mRefreshRate);

    glfwMakeContextCurrent(mWindow);
}

Window::~Window()
{
    delete mInput;
    glfwDestroyWindow(mWindow);
    glfwTerminate();
}

void Window::setWindowMode(WindowMode mode)
{
    //already in this mode, what's the point
    if(mode == mWindowMode)
        return;


    auto size = getSize();

    if(mode == WindowMode::FULLSCREEN)
    {
        glfwSetWindowMonitor(mWindow, glfwGetPrimaryMonitor(), 0, 0, size.getWidth(), size.getHeight(), mRefreshRate);
        mWindowMode = mode;
        return;
    }

    else if(mode == WindowMode::DEFAULT)
    {
        glfwSetWindowMonitor(mWindow, nullptr, 0, 0, size.getWidth(), size.getHeight(), mRefreshRate);
        mWindowMode = mode;
        return;
    }

    else if(mode == WindowMode::BORDERLESS_FULLSCREEN)
    {
        std::cout << "Borderless Fullscreen is not yet implemented!" << std::endl;
    }
}

void Window::setRefreshRate(int rate)
{
    mRefreshRate = rate;
    glfwWindowHint(GLFW_REFRESH_RATE, mRefreshRate);
}

InputManager* Window::getInputManager()
{
    return mInput;
}

GLFWwindow* Window::getGLFWwindow() const
{
    return mWindow;
}

void Window::setTitle(const std::string& title)
{
    glfwSetWindowTitle(getGLFWwindow(), title.c_str());
}

void Window::setSizeLimits(const Vector2i& min, const Vector2i& max)
{
    glfwSetWindowSizeLimits(getGLFWwindow(), min.getWidth(), min.getHeight(), max.getWidth(), max.getHeight());
}

void Window::setSize(const Vector2i& size)
{
    glfwSetWindowSize(getGLFWwindow(), size.getWidth(), size.getHeight());
}

void Window::iconify()
{
    glfwIconifyWindow(getGLFWwindow());
}

void Window::restore()
{
    glfwRestoreWindow(getGLFWwindow());
}

void Window::show()
{
    glfwShowWindow(getGLFWwindow());
}

bool Window::hasFocus() const
{
    return glfwGetWindowAttrib(getGLFWwindow(), GLFW_FOCUSED);
}
bool Window::isIconified() const
{
    return glfwGetWindowAttrib(getGLFWwindow(), GLFW_ICONIFIED);
}
bool Window::isMaximized() const
{
    return glfwGetWindowAttrib(getGLFWwindow(), GLFW_MAXIMIZED);
}
bool Window::isVisible() const
{
    return glfwGetWindowAttrib(getGLFWwindow(), GLFW_VISIBLE);
}
bool Window::isResizable() const
{
    return glfwGetWindowAttrib(getGLFWwindow(), GLFW_RESIZABLE);
}
bool Window::isDecorated() const
{
    return glfwGetWindowAttrib(getGLFWwindow(), GLFW_DECORATED);
}
bool Window::isAlwaysOnTop() const
{
    return glfwGetWindowAttrib(getGLFWwindow(), GLFW_FLOATING);
}

Vector2i Window::getSize() const
{
    int width, height;

    glfwGetWindowSize(mWindow, &width, &height);

    return Vector2i(width, height);
}

void Window::swapBuffers() const
{
    //swap our buffers
    glfwSwapBuffers(mWindow);
}

}
