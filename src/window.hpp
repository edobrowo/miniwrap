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
    Window(const std::string& title, const size_t width, const size_t height);

    void init();
    SDL_Window* window() const;
    SDL_Surface* surface() const;
    size_t width() const;
    size_t height() const;

private:
    std::string m_title;
    size_t m_width;
    size_t m_height;
    std::unique_ptr<SDL_Window, SDL_WindowDeleter> m_sdlWindow;
};

struct WindowSettings {
    std::string title;
    size_t width;
    size_t height;
};

#endif
