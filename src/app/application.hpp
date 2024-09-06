#ifndef __APPLICATION__
#define __APPLICATION__

#include <SDL2/SDL.h>

#include <memory>
#include <vector>

#include "eventloop.hpp"
#include "renderer.hpp"
#include "widget.hpp"
#include "window.hpp"

class Application {
public:
    using WidgetPtr = std::unique_ptr<Widget>;

    Application(const std::string& title, const size_t window_width, const size_t window_height);
    ~Application();

    void init();

    void addWidget(WidgetPtr widget);
    void start();

    void event(const SDL_Event& event);
    void tick();

private:
    void update();
    void render();

    void quit();

    Window m_mainWindow;
    EventLoop m_loop;
    Renderer m_renderer;

    std::vector<WidgetPtr> m_widgets;
};

#endif
