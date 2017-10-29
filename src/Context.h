#ifndef __CONTEXT_H
#define __CONTEXT_H

#include "Common.h"
#include <string>
#include <unordered_map>

struct WindowInfo{
    int width;
    int height;
    std::string title;
    bool is_full_screen;
};

enum class Control{
    CTRL_NONTHING,
    CTRL_LEFT,
    CTRL_RIGHT,
    CTRL_UP,
    CTRL_DOWN,
    CTRL_RESET,
    CTRL_ZOOM_IN,
    CTRL_ZOOM_OUT,
};

class EventDispatcher{
public:
    EventDispatcher()=default;
    virtual ~EventDispatcher(){}
    virtual void dispatchKeyPressed(int key)=0;
    virtual void dispatchScroll(double xoffset, double yoffset)=0;
};

// glfw context implementation
class Context{
public:
    Context(const WindowInfo &wi);
    virtual ~Context();

    void poll();    // return immediately
    void wait();    // wait until event happen
    void swapBuffer();
    bool shouldClose();

    class EventHandler{
    public:
        typedef int KeyType;      //GLFW_KEY_*
        typedef std::unordered_map<KeyType, Control> KeyMapType;
    
        static Control getKeyControl(KeyType key);
        static Control getScrollControl(double x, double y);

        static EventDispatcher* m_dispather;
        static GLFWwindow* m_window;
        static Context * m_context;
        //static void set_steady_handler(EventDispatcher* _steady_handler){steady_handler=_steady_handler;}
        static void setDispacher(EventDispatcher * dispatcher);
        static void setWindowHandlers();
        static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
        static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
        static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
        static void errorCallBack(int error, const char* description);
        static KeyMapType key_map;
    private:
        EventHandler(){}
        virtual ~EventHandler(){}
    };

private:
    GLFWwindow* window;
};

#endif