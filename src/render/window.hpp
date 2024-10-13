#pragma once

#include <SDL2/SDL.h>

#include <memory>
#include <string>

#include "common.hpp"

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
    Window(const u32 width, const u32 height);
    Window(const std::string& title, const u32 width, const u32 height);
    ~Window() = default;

    void init(u32 flags);
    void init();

    SDL_Window* inner() const;
    SDL_Surface* surface() const;

    const std::string& title() const;
    u32 width() const;
    u32 height() const;

private:
    std::string m_title;
    u32 m_width;
    u32 m_height;
    std::unique_ptr<SDL_Window, SDL_WindowDeleter> m_sdlWindow;
};
