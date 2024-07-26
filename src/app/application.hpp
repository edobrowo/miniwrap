#ifndef __APPLICATION__
#define __APPLICATION__

#include <SDL2/SDL.h>

#include "eventloop.hpp"
#include "renderer.hpp"
#include "window.hpp"

class Application {
public:
    Application();
    ~Application();

    virtual void setup();
    virtual void event(const SDL_Event& event) = 0;
    virtual void update() = 0;
    virtual void teardown();

    void start();
    void quit();
    const Renderer& render();

private:
    Window m_mainWindow;
    EventLoop m_loop;
    Renderer m_renderer;
};

#endif
