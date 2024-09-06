#ifndef __COMPONENT__
#define __COMPONENT__

#include <SDL2/SDL.h>

#include "renderer.hpp"

class Component {
public:
    Component();
    virtual ~Component() = 0;

    virtual void event(const SDL_Event& event);
    virtual void update();
    virtual void render(const Renderer& renderer);

    bool isRunning();

protected:
    void quit();

    bool m_running;
};

#endif
