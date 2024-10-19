#pragma once

#include <SDL2/SDL.h>

#include <memory>
#include <vector>

#include "color.hpp"
#include "common.hpp"
#include "point.hpp"
#include "rect.hpp"
#include "window.hpp"

class SDL_RendererDeleter {
public:
    void operator()(SDL_Renderer* renderer) const {
        if (renderer) {
            SDL_DestroyRenderer(renderer);
        }
    }
};

class Window;

class Renderer {
public:
    Renderer() = default;

    void init(std::weak_ptr<Window> win);
    void show() const;
    void clear() const;

    void setColor(const Color& color) const;

    void pixel(const i32 x, const i32 y) const;
    void pixels(const std::vector<Point2I>& points) const;
    void line(const i32 x1, const i32 y1, const i32 x2, const i32 y2) const;
    void polyline(const std::vector<Point2I>& points) const;
    void rectFill(const i32 x, const i32 y, const i32 width,
                  const i32 height) const;
    void rectOutline(const i32 x, const i32 y, const i32 width,
                     const i32 height) const;
    void circleFill(const i32 x, const i32 y, const i32 radius) const;
    void circleOutline(const i32 x, const i32 y, const i32 radius) const;

private:
    std::unique_ptr<SDL_Renderer, SDL_RendererDeleter> m_sdlRenderer;
};
