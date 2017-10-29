#include "Context.h"
#include <iostream>
#include <cstdlib>


Context::Context(const WindowInfo &wi){
    if (!glfwInit())
        std::exit(EXIT_FAILURE);
    /* glfw window and context */
    //glfwWindowHint(GLFW_SAMPLES, config.w_aa);

    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #ifdef _MSAA_
    // color/depth/stencil affected
    glfwWindowHint(GLFW_SAMPLES, 4);
    #endif

    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(wi.width, wi.height, wi.title.c_str(), NULL, NULL);
    if( window == NULL ){
        std::cout<<"glfwCreateWindow fail"<<std::endl;
        std::exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);


    glewExperimental = GL_TRUE;
    glewInit();

    EventHandler::m_window = this->window;
    EventHandler::setWindowHandlers();

    std::cout<<"Opengl Version: "<<glGetString(GL_VERSION)<<std::endl;
    std::cout<<"GLSL Version: "<<glGetString(GL_SHADING_LANGUAGE_VERSION)<<std::endl;

    /* some global config */
    glEnable(GL_DEPTH_TEST);
    #ifdef _MSAA_
    glEnable(GL_MULTISAMPLE);
    #endif
    glDepthFunc(GL_LEQUAL);
}
Context::~Context(){
    glfwDestroyWindow(window);
    glfwTerminate();
    //std::cout<<"Context dtor"<<std::endl;
}

void Context::poll(){
    glfwPollEvents();
}
void Context::wait(){
    glfwWaitEvents();
}
void Context::swapBuffer(){
    glfwSwapBuffers(window);
}
bool Context::shouldClose(){
    return glfwWindowShouldClose(window)?true:false;
}


/*------------------------------------------------------------------------------------------*/

EventDispatcher* Context::EventHandler::m_dispather=nullptr;
GLFWwindow* Context::EventHandler::m_window=nullptr;
Context * Context::EventHandler::m_context=nullptr;
Context::EventHandler::KeyMapType Context::EventHandler::key_map={
    {GLFW_KEY_W, Control::CTRL_UP},
    {GLFW_KEY_S, Control::CTRL_DOWN},
    {GLFW_KEY_A, Control::CTRL_LEFT},
    {GLFW_KEY_D, Control::CTRL_RIGHT},
    {GLFW_KEY_R, Control::CTRL_RESET},
};

Control Context::EventHandler::getKeyControl(KeyType key){
    auto ctrl = key_map.find(key);
    if(ctrl == key_map.end())
        return Control::CTRL_NONTHING;
    return ctrl->second;
}
Control Context::EventHandler::getScrollControl(double x, double y){
    Control ctrl = Control::CTRL_NONTHING;
    if(x == 0.0){
        if(y>0)
            ctrl = Control::CTRL_ZOOM_IN;
        else if(y<0)
            ctrl = Control::CTRL_ZOOM_OUT;
    }
    return ctrl;
}
void Context::EventHandler::setDispacher(EventDispatcher * dispatcher){
    m_dispather = dispatcher;
}
void Context::EventHandler::setWindowHandlers(){
    glfwSetErrorCallback(errorCallBack);
    glfwSetFramebufferSizeCallback(m_window, framebufferSizeCallback);
    glfwSetKeyCallback(m_window, keyCallback);
    glfwSetScrollCallback(m_window, scrollCallback);
}

void Context::EventHandler::framebufferSizeCallback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}
void Context::EventHandler::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods){
    if(action == GLFW_PRESS || action == GLFW_REPEAT){
        //std::cout<<"KEY: "<<key<<std::endl;
        if(m_dispather)
            m_dispather->dispatchKeyPressed(key);
    }
}
void Context::EventHandler::scrollCallback(GLFWwindow* window, double xoffset, double yoffset){
    if(m_dispather)
        m_dispather->dispatchScroll(xoffset, yoffset);
}
void Context::EventHandler::errorCallBack(int error, const char* description){
    std::cerr<<"Error GLFW("<<error<<"):"<<description<<std::endl;
}