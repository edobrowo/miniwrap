#pragma once

#include <SDL2/SDL.h>

#include <memory>
#include <string>

#include "common.hpp"
#include "point.hpp"

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
    Window() = default;
    ~Window() = default;

    void init(const std::string& title, const i32 x, const i32 y,
              const u32 width, const u32 height);
    void init(const std::string& title, const u32 width, const u32 height);
    void init(const u32 width, const u32 height);

    SDL_Window* inner() const;
    SDL_Surface* surface() const;

    std::string title() const;
    void setTitle(const std::string& title);

    Point2I pos() const;
    i32 x() const;
    i32 y() const;
    void setPos(const i32 x, const i32 y);
    void setX(const i32 x);
    void setY(const i32 y);

    Point2I dims() const;
    u32 width() const;
    u32 height() const;
    void setDims(const u32 width, const u32 height);
    void setWidth(const u32 width);
    void setHeight(const u32 height);

private:
    std::unique_ptr<SDL_Window, SDL_WindowDeleter> m_sdlWindow;
};
