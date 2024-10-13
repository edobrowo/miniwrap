#include "window.hpp"

#include "format.hpp"

Window::Window(const u32 width, const u32 height)
    : m_title(""), m_width(width), m_height(height) {}

Window::Window(const std::string& title, const u32 width, const u32 height)
    : m_title(title), m_width(width), m_height(height) {}

void Window::init(u32 flags) {
    SDL_Window* win = SDL_CreateWindow(m_title.c_str(), SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED, m_width,
                                       m_height, static_cast<Uint32>(flags));

    if (!win) {
        StringBuffer sb;
        format(sb, "Failed to create SDL window: {}", SDL_GetError());
        throw std::runtime_error(sb.str());
    }

    m_sdlWindow.reset(win);
}

void Window::init() { init(0); }

SDL_Window* Window::inner() const { return m_sdlWindow.get(); }

SDL_Surface* Window::surface() const {
    return SDL_GetWindowSurface(m_sdlWindow.get());
}

const std::string& Window::title() const { return m_title; }

u32 Window::width() const { return m_width; }

u32 Window::height() const { return m_height; }
