#pragma once

#include "common.hpp"
#include "timer.hpp"

class Application;

class EventLoop {
public:
    EventLoop();

    void start(Application& app, const u64 fps);
    void quit();

private:
    void run(Application& app, const u64 fps);

    bool m_running;
};
