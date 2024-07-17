#ifndef __EVENT_LOOP__
#define __EVENT_LOOP__

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

#endif
