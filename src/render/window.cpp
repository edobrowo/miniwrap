#include "window.hpp"

#include "format.hpp"

void Window::init(const std::string& title, const i32 x, const i32 y,
                  const u32 width, const u32 height) {
    if (m_sdlWindow.get())
        return;

    u32 flags = 0;
    SDL_Window* win = SDL_CreateWindow(title.c_str(), x, y, width, height,
                                       static_cast<Uint32>(flags));

    if (!win) {
        StringBuffer sb;
        format(sb, "Failed to create SDL window: {}", SDL_GetError());
        throw std::runtime_error(sb.str());
    }

    m_sdlWindow.reset(win);
}

void Window::init(const std::string& title, const u32 width, const u32 height) {
    init(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height);
}

void Window::init(const u32 width, const u32 height) {
    init("", width, height);
}

SDL_Window* Window::inner() const { return m_sdlWindow.get(); }

SDL_Surface* Window::surface() const {
    return SDL_GetWindowSurface(m_sdlWindow.get());
}

std::string Window::title() const {
    const char* title = SDL_GetWindowTitle(m_sdlWindow.get());
    return std::string(title);
}

void Window::setTitle(const std::string& title) {
    SDL_SetWindowTitle(m_sdlWindow.get(), title.c_str());
}

Point2I Window::pos() const {
    i32 x, y;
    SDL_GetWindowPosition(m_sdlWindow.get(), &x, &y);
    return Point2I(x, y);
}

i32 Window::x() const { return pos().x; }

i32 Window::y() const { return pos().y; }

void Window::setPos(const i32 x, const i32 y) {
    SDL_SetWindowPosition(m_sdlWindow.get(), x, y);
}

void Window::setX(const i32 x) {
    SDL_SetWindowPosition(m_sdlWindow.get(), x, y());
}

void Window::setY(const i32 y) {
    SDL_SetWindowPosition(m_sdlWindow.get(), x(), y);
}

Point2I Window::dims() const {
    i32 w, h;
    SDL_GetWindowSize(m_sdlWindow.get(), &w, &h);
    return Point2I(w, h);
}

u32 Window::width() const { return static_cast<u32>(dims().x); }

u32 Window::height() const { return static_cast<u32>(dims().y); }

void Window::setDims(const u32 width, const u32 height) {
    SDL_SetWindowSize(m_sdlWindow.get(), static_cast<i32>(width),
                      static_cast<i32>(height));
}

void Window::setWidth(const u32 width) {
    SDL_SetWindowSize(m_sdlWindow.get(), static_cast<i32>(width), height());
}
void Window::setHeight(const u32 height) {
    SDL_SetWindowSize(m_sdlWindow.get(), width(), static_cast<i32>(height));
}
