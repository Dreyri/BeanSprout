#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

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
    void setSizeLimits(const glm::ivec2& min, const glm::ivec2& max);
    void setSize(const glm::ivec2& size);

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

    glm::ivec2 getSize() const;

    void swapBuffers() const;
private:
    void setInputManager(InputManager* input);
};
}

#endif /* WINDOW_H */
