#include "Application.h"
#include <chrono>
#include <iostream>

namespace {
    const WindowInfo default_window_info = {.width = 1080, .height = 720, .title="magnolia", .is_full_screen=false};
    const int default_FPS = 60;
}
Application::Application():
    Context(default_window_info)
{
    frame_cnt = 0;
}
Application::~Application(){

}
void Application::startMainLoop(){
    Context & ctx = getContext();
    while(!ctx.shouldClose()){
        auto time_start = std::chrono::steady_clock::now();
        auto time_next = time_start + std::chrono::microseconds(1000000 / default_FPS);
        //scene.render_frame();
        ctx.swapBuffer();
        ctx.poll();

        frame_cnt++;  // safe for atomic
        // we fix FPS in main thread
        std::this_thread::sleep_until(time_next);
        std::cout<<"render frame:"<<frame_cnt<<std::endl;
    }
}