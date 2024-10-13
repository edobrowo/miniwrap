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

struct RGB32 {
    Uint8 r;
    Uint8 g;
    Uint8 b;
    Uint8 a;
};

class Window;

class Renderer {
public:
    Renderer() = default;

    void init(std::weak_ptr<Window> win);

    void show() const;
    void clear(const Color& color) const;

    void setColor(const Color& color) const;

    void pixel(const i32 x, const i32 y) const;
    void pixel(const Point2I& point) const;

    void line(const i32 x1, const i32 y1, const i32 x2, const i32 y2) const;
    void line(const Point2I& p1, const Point2I& p2) const;

    void rectFill(const i32 x, const i32 y, const i32 width,
                  const i32 height) const;
    void rectFill(const Rect2I& rect) const;

    void rectOutline(const i32 x, const i32 y, const i32 width,
                     const i32 height) const;
    void rectOutline(const Rect2I& rect) const;

    void polyline(const std::vector<Point2I>& points) const;

private:
    static RGB32 toRgb32(const Color& color);

    std::unique_ptr<SDL_Renderer, SDL_RendererDeleter> m_sdlRenderer;
    Size m_windowWidth;
    i32 m_windowHeight;
};
