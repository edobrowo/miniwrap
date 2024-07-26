#include "application.hpp"

Application::Application() : m_mainWindow{"Title", 640, 640}, m_loop{}, m_renderer{} {
    int err = SDL_InitSubSystem(SDL_INIT_VIDEO);
    if (err != 0) {
        std::string message = std::string("Failed to update SDL window") + SDL_GetError();
        throw std::runtime_error(message);
    }

    m_mainWindow.init();

    std::shared_ptr<Window> window_ref(&m_mainWindow, [](auto) {});
    m_renderer.init(window_ref);
}

Application::~Application() {
    SDL_Quit();
}

void Application::setup() {
    //
}

void Application::teardown() {
    //
}

void Application::start() {
    setup();
    m_loop.start(*this);
}

void Application::quit() {
    m_loop.quit();
    teardown();
}

const Renderer& Application::render() {
    return m_renderer;
}
