#ifndef __WINDOW__
#define __WINDOW__

#include <SDL2/SDL.h>

#include <memory>
#include <string>

class SDL_WindowDeleter {
public:
    void operator()(SDL_Window* window) const {
        if (window) {
            SDL_FreeSurface(SDL_GetWindowSurface(window));
            SDL_DestroyWindow(window);
        }
    }
};

class Window {
public:
    Window(const size_t width, const size_t height);
    Window(const std::string& title, const size_t width, const size_t height);
    ~Window();

    void init(uint32_t flags);
    void init();

    SDL_Window* inner() const;
    SDL_Surface* surface() const;

    std::string title() const noexcept;
    size_t width() const noexcept;
    size_t height() const noexcept;

private:
    std::string m_title;
    size_t m_width;
    size_t m_height;
    std::unique_ptr<SDL_Window, SDL_WindowDeleter> m_sdlWindow;
};

#endif
