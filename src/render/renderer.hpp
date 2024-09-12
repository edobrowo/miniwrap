#ifndef __RENDERER__
#define __RENDERER__

#include <SDL2/SDL.h>

#include <memory>
#include <vector>

#include "color.hpp"
#include "line.hpp"
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

    void pixel(const int x, const int y) const;
    void pixel(const Point& point) const;

    void line(const int x1, const int y1, const int x2, const int y2) const;
    void line(const Point& p1, const Point& p2) const;
    void line(const Line& line) const;

    void rectFill(const int x, const int y, const int width,
                  const int height) const;
    void rectFill(const Rect& rect) const;

    void rectOutline(const int x, const int y, const int width,
                     const int height) const;
    void rectOutline(const Rect& rect) const;

    void polyline(const std::vector<Point>& points) const;

private:
    static RGB32 toRgb32(const Color& color);

    std::unique_ptr<SDL_Renderer, SDL_RendererDeleter> m_sdlRenderer;
    int m_windowWidth;
    int m_windowHeight;
};

#endif
