#include "window.hpp"

Window::Window(const std::string& title, const size_t width, const size_t height)
    : m_title{title}, m_width{width}, m_height{height} {}

void Window::init() {
    SDL_Window* win = SDL_CreateWindow(m_title.c_str(),
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       m_width, m_height, 0);

    if (!win) {
        std::string message = std::string("Failed to create SDL window") + SDL_GetError();
        throw std::runtime_error(message);
    }

    m_sdlWindow.reset(win);
}

SDL_Window* Window::window() const {
    return m_sdlWindow.get();
}

SDL_Surface* Window::surface() const {
    return SDL_GetWindowSurface(m_sdlWindow.get());
}

size_t Window::width() const {
    return m_width;
}

size_t Window::height() const {
    return m_height;
}
