#include "application.hpp"

Application::Application(const std::string& title, const size_t window_width, const size_t window_height)
    : m_mainWindow{title, window_width, window_height}, m_loop{}, m_renderer{} {
}

Application::~Application() {
    SDL_Quit();
}

void Application::init() {
    int err = SDL_InitSubSystem(SDL_INIT_VIDEO);
    if (err != 0) {
        std::string message = std::string("Failed to update SDL window") + SDL_GetError();
        throw std::runtime_error(message);
    }

    m_mainWindow.init();

    std::shared_ptr<Window> window_ref(&m_mainWindow, [](auto) {});
    m_renderer.init(window_ref);
}

void Application::addComponent(ComponentPtr widget) {
    m_components.push_back(std::move(widget));
}

void Application::start() {
    m_loop.start(*this);
}

void Application::event(const SDL_Event& event) {
    for (ComponentPtr& wptr : m_components) {
        wptr->event(event);
    }
}

void Application::tick() {
    update();
    render();
}

void Application::update() {
    for (ComponentPtr& wptr : m_components) {
        wptr->update();
        if (!wptr->isRunning()) {
            quit();
        }
    }
}

void Application::render() {
    for (ComponentPtr& wptr : m_components) {
        wptr->render(m_renderer);
    }
}

void Application::quit() {
    m_loop.quit();
}
