#ifndef __APPLICATION__
#define __APPLICATION__

#include <memory>
#include <vector>

#include "component.hpp"
#include "event.hpp"
#include "eventloop.hpp"
#include "renderer.hpp"
#include "window.hpp"

class Application {
public:
    using ComponentPtr = std::unique_ptr<Component>;

    Application(const std::string& title, const size_t window_width,
                const size_t window_height);
    ~Application();

    void init();

    void addComponent(ComponentPtr widget);
    void start();

    void event(const Event* event);
    void tick();

private:
    void update();
    void render();

    void quit();

    Window m_mainWindow;
    EventLoop m_loop;
    Renderer m_renderer;

    std::vector<ComponentPtr> m_components;
};

#endif
