#pragma once

#include <memory>
#include <vector>

#include "common.hpp"
#include "component.hpp"
#include "event.hpp"
#include "eventloop.hpp"
#include "format.hpp"
#include "frameinfo.hpp"
#include "renderer.hpp"
#include "window.hpp"

constexpr u64 FPS_MAX = 1000;

class Application {
public:
    using ComponentPtr = std::unique_ptr<Component>;

    Application(const std::string& title, const u32 window_width,
                const u32 window_height);
    ~Application();

    void init();

    void addComponent(ComponentPtr widget);
    void start(const u64 fps);

    void event(const Event* event);
    void tick(const FrameInfo& info);

private:
    void update(const FrameInfo& info);
    void render();

    void quit();

    Window m_mainWindow;
    EventLoop m_loop;
    Renderer m_renderer;

    std::vector<ComponentPtr> m_components;
};
