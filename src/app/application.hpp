#ifndef __APPLICATION__
#define __APPLICATION__

#include <SDL2/SDL.h>

#include <vector>

#include "eventloop.hpp"
#include "renderer.hpp"
#include "vec2.hpp"
#include "window.hpp"

class Application {
public:
    Application();

    void start();
    void event(const SDL_Event& event);
    void update();

private:
    Window m_mainWindow;
    EventLoop m_loop;
    Renderer m_renderer;

    std::vector<Vec2> m_joints;
    const Color m_clearColor{0, 0, 0};
    const Color m_armColor{255, 0, 0};
};

#endif
