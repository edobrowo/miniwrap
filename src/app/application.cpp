#include "application.hpp"

#include <SDL2/SDL.h>

#include <iostream>

#include "event_builder.hpp"

Application::Application(const std::string& title, const u32 window_width,
                         const u32 window_height)
    : m_mainWindow(title, window_width, window_height),
      m_loop(),
      m_renderer() {}

Application::~Application() { SDL_Quit(); }

void Application::init() {
    i32 err = SDL_InitSubSystem(SDL_INIT_VIDEO);
    if (err != 0) {
        StringBuffer sb;
        format(sb, "Failed to initialize SDL subsystem: {}", SDL_GetError());
        throw std::runtime_error(sb.str());
    }

    m_mainWindow.init();

    std::shared_ptr<Window> window_ref(&m_mainWindow, [](auto) {});
    m_renderer.init(window_ref);
}

void Application::addComponent(ComponentPtr widget) {
    m_components.push_back(std::move(widget));
}

void Application::start() { m_loop.start(*this); }

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
    for (ComponentPtr& cptr : m_components) {
        cptr->render(m_renderer);
    }
}

void Application::quit() { m_loop.quit(); }
