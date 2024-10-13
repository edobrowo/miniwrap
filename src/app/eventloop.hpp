#pragma once

class Application;

class EventLoop {
public:
    EventLoop();

    void start(Application& app);
    void quit();

private:
    void run(Application& app);

    bool m_running;
};
