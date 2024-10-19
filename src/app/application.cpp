#include "application.hpp"

#include <SDL2/SDL.h>

#include <iostream>

#include "event_builder.hpp"

Application::~Application() { SDL_Quit(); }

void Application::init(const std::string& title, const u32 window_width,
                       const u32 window_height) {
    i32 err = SDL_InitSubSystem(SDL_INIT_VIDEO);
    if (err != 0) {
        StringBuffer sb;
        format(sb, "Failed to initialize SDL subsystem: {}", SDL_GetError());
        throw std::runtime_error(sb.str());
    }

    m_mainWindow.init(title, window_width, window_height);

    std::shared_ptr<Window> window_ref(&m_mainWindow, [](auto) {});
    m_renderer.init(window_ref);

    m_canvas.init(&m_renderer, window_width, window_height);
}

const Window& Application::window() const { return m_mainWindow; }

Window& Application::windowMut() { return m_mainWindow; }

void Application::add(ComponentPtr component) {
    m_components.push_back(std::move(component));
}

void Application::start(const u64 fps) {
    assert(fps <= FPS_MAX);
    m_loop.start(*this, fps);
}

void Application::event(const Event* event) {
    for (ComponentPtr& cptr : m_components) {
        cptr->event(event);
    }
}

void Application::tick() {
    update();
    render();
}

void Application::update() {
    for (ComponentPtr& cptr : m_components) {
        cptr->update();
        if (!cptr->isRunning()) {
            quit();
        }
    }
}

void Application::render() {
    m_renderer.clear();
    for (ComponentPtr& cptr : m_components) {
        cptr->draw(m_canvas);
    }
    m_renderer.show();
}

void Application::quit() { m_loop.quit(); }
