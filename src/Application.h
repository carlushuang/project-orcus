#ifndef __APPLICATION_H
#define __APPLICATION_H

#include <string>
#include <atomic>
#include <thread>
#include "Context.h"

class Application : public Context{
public:

    Application();
    ~Application();
    void startMainLoop();

    Context & getContext(){return *this;}
private:
    std::atomic_int frame_cnt;
    std::atomic_bool thread_should_exit;
    std::thread fps_thread;

    void draw_frame();
};

#endif