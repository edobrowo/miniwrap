#include "renderer.hpp"

void Renderer::init(std::weak_ptr<Window> win) {
    std::shared_ptr<Window> window_ref = win.lock();
    if (!window_ref) {
        std::string message = std::string("Invalid window weak_ptr");
        throw std::runtime_error(message);
    }

    m_windowWidth = window_ref->width();
    m_windowHeight = window_ref->height();

    SDL_Renderer* ren = SDL_CreateRenderer(window_ref->window(), -1, SDL_RENDERER_ACCELERATED);

    if (!ren) {
        std::string message = std::string("Failed to create SDL renderer: ") + SDL_GetError();
        throw std::runtime_error(message);
    }

    m_sdlRenderer.reset(ren);
}

void Renderer::displayFrame() const {
    SDL_RenderPresent(m_sdlRenderer.get());
}

void Renderer::clear(const Color& color) const {
    RGB32 rgb = toRgb32(color);
    SDL_SetRenderDrawColor(m_sdlRenderer.get(), rgb.r, rgb.g, rgb.b, rgb.a);
    SDL_RenderClear(m_sdlRenderer.get());
}

void Renderer::pixel(const Pixel& pixel, const Color& color) const {
    RGB32 rgb = toRgb32(color);
    SDL_SetRenderDrawColor(m_sdlRenderer.get(), rgb.r, rgb.g, rgb.b, rgb.a);

    SDL_RenderDrawPoint(m_sdlRenderer.get(), pixel.x, pixel.y);
}

void Renderer::line(const Line& line, const Color& color) const {
    RGB32 rgb = toRgb32(color);
    SDL_SetRenderDrawColor(m_sdlRenderer.get(), rgb.r, rgb.g, rgb.b, rgb.a);

    SDL_RenderDrawLine(m_sdlRenderer.get(), line.x1, line.y1, line.x2, line.y2);
}

void Renderer::rectAreaFill(const RectangleRegion& rect, const Color& color) const {
    RGB32 rgb = toRgb32(color);
    SDL_SetRenderDrawColor(m_sdlRenderer.get(), rgb.r, rgb.g, rgb.b, rgb.a);

    SDL_Rect fillRect = {rect.x, rect.y, rect.width, rect.height};
    SDL_RenderFillRect(m_sdlRenderer.get(), &fillRect);
}

void Renderer::rectAreaOutline(const RectangleRegion& rect, const Color& color) const {
    RGB32 rgb = toRgb32(color);
    SDL_SetRenderDrawColor(m_sdlRenderer.get(), rgb.r, rgb.g, rgb.b, rgb.a);

    SDL_Rect outlineRect = {rect.x, rect.y, rect.width, rect.height};
    SDL_RenderDrawRect(m_sdlRenderer.get(), &outlineRect);
}

void Renderer::circleAreaFill(const CircleRegion& circle, const Color& color) const {
    // TODO
}

void Renderer::circleAreaOutline(const CircleRegion& circle, const Color& color) const {
    // TODO
}

RGB32 Renderer::toRgb32(const Color& color) {
    return RGB32{
        static_cast<Uint8>(color.r() * 255),
        static_cast<Uint8>(color.g() * 255),
        static_cast<Uint8>(color.b() * 255),
        static_cast<Uint8>(color.a() * 255)};
}
