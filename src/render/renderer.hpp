#ifndef __RENDERER__
#define __RENDERER__

#include <SDL2/SDL.h>

#include <memory>

#include "color.hpp"
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

struct Line {
    int x1;
    int y1;
    int x2;
    int y2;
};

class Window;

class Renderer {
public:
    Renderer() = default;

    void init(std::weak_ptr<Window> win);

    // Display the next frame
    void displayFrame() const;

    // Clear the viewport
    void clear(const Color& color) const;

    // Draw a point
    void pixel(const Point& point, const Color& color) const;

    // Draw a line
    void line(const Line& line, const Color& color) const;

    // Draw a filled rectangle
    void rectFill(const Rect& rect, const Color& color) const;

    // Draw an outlined rectangle
    void rectOutline(const Rect& rect, const Color& color) const;

private:
    static RGB32 toRgb32(const Color& color);

    std::unique_ptr<SDL_Renderer, SDL_RendererDeleter> m_sdlRenderer;
    int m_windowWidth;
    int m_windowHeight;
};

#endif
