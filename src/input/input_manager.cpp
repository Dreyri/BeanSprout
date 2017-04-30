#include "input_manager.h"

#include <GLFW/glfw3.h>
#include <iostream>
#include <algorithm>
#include "../graphics/window.h"

namespace BS
{

InputManager::InputManager(Window* window)
    : mWindow(window)
{
    if(mWindow != nullptr)
        init();
}

void InputManager::init()
{
    //register to all callbacks
    if(mWindow == nullptr)
        return;

    auto mouseButtonCB = [](GLFWwindow* window, int button, int action, int mods)
    {
        Window* w = static_cast<Window*>(glfwGetWindowUserPointer(window));

        InputManager* input = w->getInputManager();
        if(input != nullptr)
        {
            input->getMouseButtonSignal()(button, action, mods);
        }
        else
        {
            std::cout <<  "No input manager registered to window, this shouldn't happen!" << std::endl;
        }
    };

    auto setKeyCB = [](GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        Window* w = static_cast<Window*>(glfwGetWindowUserPointer(window));

        InputManager* input = w->getInputManager();
        if(input != nullptr)
        {
            input->getKeySignal()(key, scancode, action, mods);
        }
        else
        {
            std::cout << "No input manager registered to window, this shouldn't happen!" << std::endl;
        }
    };

    auto cursorPosCB = [](GLFWwindow* window, double xpos, double ypos)
    {
        Window* w = static_cast<Window*>(glfwGetWindowUserPointer(window));

        InputManager* input = w->getInputManager();
        if(input != nullptr)
        {
            input->getCursorPosSignal()(xpos, ypos);
        }
        else
        {
            std::cout << "No input manager registered to window, this shouldn't happen!" << std::endl;
        }
    };

    auto closeCB = [](GLFWwindow* window)
    {
        Window* w = static_cast<Window*>(glfwGetWindowUserPointer(window));

        InputManager* input = w->getInputManager();
        if(input != nullptr)
        {
            input->getCloseSignal()();
        }
        else
        {
            std::cout << "No input manager registered to window, this shouldn't happen!" << std::endl;
        }
    };

    auto sizeCB = [](GLFWwindow* window, int width, int height)
    {
        Window* w = static_cast<Window*>(glfwGetWindowUserPointer(window));

        InputManager* input = w->getInputManager();
        if(input != nullptr)
        {
            input->getSizeSignal()(width, height);
        }
        else
        {
            std::cout << "No input manager registered to window, this shouldn't happen!" << std::endl;
        }
    };

    auto framebufferSizeCB = [](GLFWwindow* window, int width, int height)
    {
        Window* w = static_cast<Window*>(glfwGetWindowUserPointer(window));

        InputManager* input = w->getInputManager();
        if(input != nullptr)
        {
            input->getFramebufferSizeSignal()(width, height);
        }
        else
        {
            std::cout << "No input manager registered to window, this shouldn't happen!" << std::endl;
        }
    };

    auto posCB = [](GLFWwindow* window, int xpos, int ypos)
    {
        Window* w = static_cast<Window*>(glfwGetWindowUserPointer(window));

        InputManager* input = w->getInputManager();
        if(input != nullptr)
        {
            input->getPosSignal()(xpos, ypos);
        }
        else
        {
            std::cout << "No input manager registered to window, this shouldn't happen!" << std::endl;
        }
    };

    auto iconifyCB = [](GLFWwindow* window, int iconified)
    {
        Window* w = static_cast<Window*>(glfwGetWindowUserPointer(window));

        InputManager* input = w->getInputManager();
        if(input != nullptr)
        {
            input->getIconifySignal()(iconified);
        }
        else
        {
            std::cout << "No input manager registered to window, this shouldn't happen!" << std::endl;
        }
    };

    auto focusCB = [](GLFWwindow* window, int focused)
    {
        Window* w = static_cast<Window*>(glfwGetWindowUserPointer(window));

        InputManager* input = w->getInputManager();
        if(input != nullptr)
        {
            input->getFocusSignal()(focused);
        }
        else
        {
            std::cout << "No input manager registered to window, this shouldn't happen!" << std::endl;
        }
    };

    auto refreshCB = [](GLFWwindow* window)
    {
        Window* w = static_cast<Window*>(glfwGetWindowUserPointer(window));

        InputManager* input = w->getInputManager();
        if(input != nullptr)
        {
            input->getRefreshSignal()();
        }
        else
        {
            std::cout << "No input manager registered to window, this shouldn't happen!" << std::endl;
        }
    };

    glfwSetMouseButtonCallback(mWindow->getGLFWwindow(), mouseButtonCB);
    glfwSetKeyCallback(mWindow->getGLFWwindow(), setKeyCB);
    glfwSetCursorPosCallback(mWindow->getGLFWwindow(), cursorPosCB);
    glfwSetWindowCloseCallback(mWindow->getGLFWwindow(), closeCB);
    glfwSetWindowSizeCallback(mWindow->getGLFWwindow(), sizeCB);
    glfwSetFramebufferSizeCallback(mWindow->getGLFWwindow(), framebufferSizeCB);
    glfwSetWindowPosCallback(mWindow->getGLFWwindow(), posCB);
    glfwSetWindowIconifyCallback(mWindow->getGLFWwindow(), iconifyCB);
    glfwSetWindowFocusCallback(mWindow->getGLFWwindow(), focusCB);
    glfwSetWindowRefreshCallback(mWindow->getGLFWwindow(), refreshCB);
}

InputManager::~InputManager()
{
}

void InputManager::pollEvents()
{
    glfwPollEvents();
}

glm::dvec2 InputManager::getCursorPosition() const
{
    double xpos, ypos;
    glfwGetCursorPos(mWindow->getGLFWwindow(), &xpos, &ypos);

    return glm::dvec2(xpos, ypos);
}

Window* InputManager::getWindow()
{
    return mWindow;
}

InputManager::MouseButtonSignal& InputManager::getMouseButtonSignal() { return mMouseSig; }
InputManager::KeySignal& InputManager::getKeySignal() { return mKeySig; }
InputManager::CursorPosSignal& InputManager::getCursorPosSignal() { return mCursorSig; }
InputManager::CloseSignal& InputManager::getCloseSignal() { return mCloseSig; }
InputManager::SizeSignal& InputManager::getSizeSignal() { return mSizeSig; }
InputManager::FramebufferSizeSignal& InputManager::getFramebufferSizeSignal() { return mFBSizeSig; }
InputManager::PosSignal& InputManager::getPosSignal() { return mPosSignal; }
InputManager::IconifySignal& InputManager::getIconifySignal() { return mIconifySignal; }
InputManager::FocusSignal& InputManager::getFocusSignal() { return mFocusSignal; }
InputManager::RefreshSignal& InputManager::getRefreshSignal() { return mRefreshSignal; }

}
