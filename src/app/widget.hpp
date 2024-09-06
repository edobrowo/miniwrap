#ifndef __WIDGET__
#define __WIDGET__

#include <SDL2/SDL.h>

#include "renderer.hpp"

class Widget {
public:
    Widget();
    virtual ~Widget();

    virtual void event(const SDL_Event& event);
    virtual void update();
    virtual void render(const Renderer& renderer);

    bool isRunning();

protected:
    void quit();

    bool m_running;
};

#endif
