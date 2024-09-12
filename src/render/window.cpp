#include "window.hpp"

Window::Window(const size_t width, const size_t height)
    : m_title{""}, m_width{width}, m_height{height} {}

Window::Window(const std::string& title, const size_t width,
               const size_t height)
    : m_title{title}, m_width{width}, m_height{height} {}

Window::~Window() {}

void Window::init(uint32_t flags) {
    SDL_Window* win = SDL_CreateWindow(m_title.c_str(), SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED, m_width,
                                       m_height, static_cast<Uint32>(flags));

    if (!win) {
        std::string message =
            std::string("Failed to create SDL window") + SDL_GetError();
        throw std::runtime_error(message);
    }

    m_sdlWindow.reset(win);
}

void Window::init() { init(0); }

SDL_Window* Window::inner() const { return m_sdlWindow.get(); }

SDL_Surface* Window::surface() const {
    return SDL_GetWindowSurface(m_sdlWindow.get());
}

size_t Window::width() const noexcept { return m_width; }

size_t Window::height() const noexcept { return m_height; }
