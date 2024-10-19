#include "renderer.hpp"

void Renderer::init(std::weak_ptr<Window> win) {
    std::shared_ptr<Window> window_ref = win.lock();
    if (!window_ref) {
        std::string message = std::string("Invalid window weak_ptr");
        throw std::runtime_error(message);
    }

    SDL_Renderer* ren =
        SDL_CreateRenderer(window_ref->inner(), -1, SDL_RENDERER_ACCELERATED);

    if (!ren) {
        StringBuffer sb;
        format(sb, "Failed to create SDL renderer: {}", SDL_GetError());
        throw std::runtime_error(sb.str());
    }

    m_sdlRenderer.reset(ren);
}

void Renderer::show() const { SDL_RenderPresent(m_sdlRenderer.get()); }

void Renderer::clear() const {
    RGB24 rgb(0);
    SDL_SetRenderDrawColor(m_sdlRenderer.get(), rgb.r(), rgb.g(), rgb.b(), 1.0);
    SDL_RenderClear(m_sdlRenderer.get());
}
void Renderer::setColor(const Color& color) const {
    RGB24 rgb(color);
    SDL_SetRenderDrawColor(m_sdlRenderer.get(), rgb.r(), rgb.g(), rgb.b(), 1.0);
}

void Renderer::pixel(const i32 x, const i32 y) const {
    SDL_RenderDrawPoint(m_sdlRenderer.get(), x, y);
}

void Renderer::pixels(const std::vector<Point2I>& points) const {
    const SDL_Point* p = reinterpret_cast<const SDL_Point*>(points.data());
    SDL_RenderDrawPoints(m_sdlRenderer.get(), p, points.size());
}

void Renderer::line(const i32 x1, const i32 y1, const i32 x2,
                    const i32 y2) const {
    SDL_RenderDrawLine(m_sdlRenderer.get(), x1, y1, x2, y2);
}

void Renderer::polyline(const std::vector<Point2I>& points) const {
    const SDL_Point* p = reinterpret_cast<const SDL_Point*>(points.data());
    SDL_RenderDrawLines(m_sdlRenderer.get(), p, points.size());
}

void Renderer::rectFill(const i32 x, const i32 y, const i32 width,
                        const i32 height) const {
    SDL_Rect fill_rect = {x, y, width, height};
    SDL_RenderFillRect(m_sdlRenderer.get(), &fill_rect);
}

void Renderer::rectOutline(const i32 x, const i32 y, const i32 width,
                           const i32 height) const {
    SDL_Rect outline_rect = {x, y, width, height};
    SDL_RenderDrawRect(m_sdlRenderer.get(), &outline_rect);
}

void Renderer::circleFill(const i32 x, const i32 y, const i32 radius) const {
    i32 t1 = radius / 16;
    i32 t2 = 0;
    i32 dx = radius;
    i32 dy = 0;

    std::vector<Point2I> points;
    points.reserve(radius * 6);

    while (dx >= dy) {
        points.emplace_back(x - dx, y + dy);
        points.emplace_back(x + dx, y + dy);

        points.emplace_back(x - dx, y - dy);
        points.emplace_back(x + dx, y - dy);

        ++dy;
        t1 += dy;
        t2 = t1 - dx;
        if (t2 >= 0) {
            points.emplace_back(x - dy + 1, y + dx);
            points.emplace_back(x + dy - 1, y + dx);

            points.emplace_back(x - dy + 1, y - dx);
            points.emplace_back(x + dy - 1, y - dx);

            t1 = t2;
            --dx;
        }
    }

    polyline(points);
}

// https://en.wikipedia.org/wiki/Midpoint_circle_algorithm
void Renderer::circleOutline(const i32 x, const i32 y, const i32 radius) const {
    i32 t1 = radius / 16;
    i32 t2 = 0;
    i32 dx = radius;
    i32 dy = 0;

    std::vector<Point2I> points;
    points.reserve(radius * 6);

    while (dx >= dy) {
        points.emplace_back(x - dx, y + dy);
        points.emplace_back(x + dx, y + dy);

        points.emplace_back(x - dx, y - dy);
        points.emplace_back(x + dx, y - dy);

        points.emplace_back(x - dy, y + dx);
        points.emplace_back(x + dy, y + dx);

        points.emplace_back(x - dy, y - dx);
        points.emplace_back(x + dy, y - dx);

        ++dy;
        t1 += dy;
        t2 = t1 - dx;
        if (t2 >= 0) {
            t1 = t2;
            --dx;
        }
    }

    pixels(points);
}
