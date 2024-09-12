#include "renderer.hpp"

void Renderer::init(std::weak_ptr<Window> win) {
    std::shared_ptr<Window> window_ref = win.lock();
    if (!window_ref) {
        std::string message = std::string("Invalid window weak_ptr");
        throw std::runtime_error(message);
    }

    m_windowWidth = window_ref->width();
    m_windowHeight = window_ref->height();

    SDL_Renderer* ren =
        SDL_CreateRenderer(window_ref->inner(), -1, SDL_RENDERER_ACCELERATED);

    if (!ren) {
        std::string message =
            std::string("Failed to create SDL renderer: ") + SDL_GetError();
        throw std::runtime_error(message);
    }

    m_sdlRenderer.reset(ren);
}

void Renderer::show() const { SDL_RenderPresent(m_sdlRenderer.get()); }

void Renderer::setColor(const Color& color) const {
    RGB32 rgb = toRgb32(color);
    SDL_SetRenderDrawColor(m_sdlRenderer.get(), rgb.r, rgb.g, rgb.b, rgb.a);
}

void Renderer::clear(const Color& color) const {
    RGB32 rgb = toRgb32(color);
    SDL_SetRenderDrawColor(m_sdlRenderer.get(), rgb.r, rgb.g, rgb.b, rgb.a);
    SDL_RenderClear(m_sdlRenderer.get());
}

void Renderer::pixel(const int x, const int y) const {
    SDL_RenderDrawPoint(m_sdlRenderer.get(), x, y);
}

void Renderer::pixel(const Point& point) const { pixel(point.x(), point.y()); }

void Renderer::line(const int x1, const int y1, const int x2,
                    const int y2) const {
    SDL_RenderDrawLine(m_sdlRenderer.get(), x1, y1, x2, y2);
}

void Renderer::line(const Point& p1, const Point& p2) const {
    line(p1.x(), p1.y(), p2.x(), p2.y());
}

void Renderer::line(const Line& drawline) const {
    line(drawline.x1(), drawline.y1(), drawline.x2(), drawline.y2());
}

void Renderer::rectFill(const int x, const int y, const int width,
                        const int height) const {
    SDL_Rect fill_rect = {x, y, width, height};
    SDL_RenderFillRect(m_sdlRenderer.get(), &fill_rect);
}

void Renderer::rectFill(const Rect& rect) const {
    rectFill(rect.x(), rect.y(), rect.width(), rect.height());
}

void Renderer::rectOutline(const int x, const int y, const int width,
                           const int height) const {
    SDL_Rect outline_rect = {x, y, width, height};
    SDL_RenderDrawRect(m_sdlRenderer.get(), &outline_rect);
}

void Renderer::rectOutline(const Rect& rect) const {
    rectOutline(rect.x(), rect.y(), rect.width(), rect.height());
}

RGB32 Renderer::toRgb32(const Color& color) {
    return RGB32{static_cast<Uint8>(color.r() * 255),
                 static_cast<Uint8>(color.g() * 255),
                 static_cast<Uint8>(color.b() * 255),
                 static_cast<Uint8>(color.a() * 255)};
}

void Renderer::polyline(const std::vector<Point>& points) const {
    if (points.size() <= 1)
        return;

    for (size_t i = 1, n = points.size(); i < n; ++i)
        line(points[i - 1], points[i]);
}
