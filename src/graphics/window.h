#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <GLFW/glfw3.h>
#include "math/vector2.h"

namespace BS
{
class InputManager;

enum class WindowMode
{
    DEFAULT,
    FULLSCREEN,
    BORDERLESS_FULLSCREEN
};

class Window
{
private:
    std::string mName;
    GLFWwindow* mWindow;
    WindowMode mWindowMode;

    InputManager* mInput;

    //int mWidth, mHeight;
    int mRefreshRate;

public:
    Window(const std::string& name, int width, int height, WindowMode mode, int refreshrate = -1);
    Window() : Window("BeanSprout", 640, 480, WindowMode::DEFAULT) {}
    virtual ~Window();

    void setWindowMode(WindowMode mode);
    void setRefreshRate(int rate);

    InputManager* getInputManager();

    GLFWwindow* getGLFWwindow() const;
    WindowMode getWindowMode() const { return mWindowMode; }

    void setTitle(const std::string& title);
    void setSizeLimits(const Vector2i& min, const Vector2i& max);
    void setSize(const Vector2i& size);

    void iconify();
    void restore();
    void show();

    bool hasFocus() const;
    bool isIconified() const;
    bool isMaximized() const;
    bool isVisible() const;
    bool isResizable() const;
    bool isDecorated() const;
    bool isAlwaysOnTop() const;

    Vector2i getSize() const;

    void swapBuffers() const;
private:
    void setInputManager(InputManager* input);
};
}

#endif /* WINDOW_H */
