#include "application.hpp"

Application::Application(const std::string& title, const size_t window_width, const size_t window_height)
    : m_mainWindow{title, window_width, window_height}, m_loop{}, m_renderer{} {
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
}

void Application::teardown() {
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
