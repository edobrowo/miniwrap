#pragma once

#include <memory>
#include <vector>

#include "canvas.hpp"
#include "common.hpp"
#include "component.hpp"
#include "event.hpp"
#include "eventloop.hpp"
#include "format.hpp"
#include "renderer.hpp"
#include "window.hpp"

constexpr u64 FPS_MAX = 1000;

class Application {
public:
    using ComponentPtr = std::unique_ptr<Component>;

    Application() = default;
    ~Application();

    void init(const std::string& title, const u32 window_width,
              const u32 window_height);

    const Window& window() const;
    Window& windowMut();

    void add(ComponentPtr widget);
    void start(const u64 fps);

    void event(const Event* event);
    void tick();

private:
    void update();
    void render();

    void quit();

    Window m_mainWindow;
    EventLoop m_loop;
    Renderer m_renderer;
    Canvas m_canvas;

    std::vector<ComponentPtr> m_components;
};
