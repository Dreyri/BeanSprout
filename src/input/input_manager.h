#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <GLFW/glfw3.h>
#include <vector>
#include "graphics/window.h"
#include "signal/signal.h"
#include "input_codes.h"

namespace BS
{

class InputManager
{
public:
    typedef Signal<void(int, int, int)> MouseButtonSignal;
    typedef Signal<void(int, int, int, int)> KeySignal;
    typedef Signal<void(double, double)> CursorPosSignal;
    typedef Signal<void()> CloseSignal;
    typedef Signal<void(int,int)> SizeSignal;
    typedef Signal<void(int,int)> FramebufferSizeSignal;
    typedef Signal<void(int,int)> PosSignal;
    typedef Signal<void(int)> IconifySignal;
    typedef Signal<void(int)> FocusSignal;
    typedef Signal<void()> RefreshSignal;
private:
    Window* mWindow;

    MouseButtonSignal mMouseSig;
    KeySignal mKeySig;
    CursorPosSignal mCursorSig;
    CloseSignal mCloseSig;
    SizeSignal mSizeSig;
    FramebufferSizeSignal mFBSizeSig;
    PosSignal mPosSignal;
    IconifySignal mIconifySignal;
    FocusSignal mFocusSignal;
    RefreshSignal mRefreshSignal;

public:
    InputManager(Window* window);
    virtual ~InputManager();

    void pollEvents();

    glm::dvec2 getCursorPosition() const;

    Window* getWindow();

    MouseButtonSignal& getMouseButtonSignal();
    KeySignal& getKeySignal();
    CursorPosSignal& getCursorPosSignal();
    CloseSignal& getCloseSignal();
    SizeSignal& getSizeSignal();
    FramebufferSizeSignal& getFramebufferSizeSignal();
    PosSignal& getPosSignal();
    IconifySignal& getIconifySignal();
    FocusSignal& getFocusSignal();
    RefreshSignal& getRefreshSignal();

private:
    void init();

    static void forwardMouseButtonCallback(GLFWwindow* window, int button, int action, int state);
    static void forwardKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void forwardCursorPosCallback(GLFWwindow* window, double xpos, double ypos);
};
}

#endif /* INPUT_MANAGER_H */
