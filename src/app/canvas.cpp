#include "canvas.hpp"

void Canvas::init(Renderer* renderer, const Size width, const Size height) {
    m_renderer = renderer;
    m_width = width;
    m_height = height;
}

Size Canvas::width() const { return m_width; }

Size Canvas::height() const { return m_height; }

void Canvas::setColor(const Color& c) const { m_renderer->setColor(c); }

void Canvas::fill(const Color& c) const {
    m_renderer->setColor(c);
    rect(0, 0, m_width, m_height);
}

void Canvas::pixel(const i32 x, const i32 y) const { m_renderer->pixel(x, y); }

void Canvas::pixel(const Point2I p) const { m_renderer->pixel(p.x, p.y); }

void Canvas::pixels(const std::vector<Point2I>& points) const {
    m_renderer->pixels(points);
}

void Canvas::line(const i32 x1, const i32 y1, const i32 x2,
                  const i32 y2) const {
    m_renderer->line(x1, y1, x2, y2);
}

void Canvas::line(const Point2I p1, const Point2I p2) const {
    m_renderer->line(p1.x, p1.y, p2.x, p2.y);
}

void Canvas::line(const Rect2I r) const {
    m_renderer->line(r.x, r.y, r.x + r.width, r.y + r.height);
}

void Canvas::polyline(const std::vector<Point2I>& points) const {
    m_renderer->polyline(points);
}

void Canvas::rect(const i32 x, const i32 y, const i32 width,
                  const i32 height) const {
    m_renderer->rectFill(x, y, width, height);
}

void Canvas::rect(const Point2I p1, const i32 width, const i32 height) const {
    m_renderer->rectFill(p1.x, p1.y, width, height);
}

void Canvas::rect(const Point2I p1, const Point2I p2) const {
    m_renderer->rectFill(p1.x, p1.y, p2.x - p1.x, p2.y - p1.y);
}

void Canvas::rect(const Rect2I r) const {
    m_renderer->rectFill(r.x, r.y, r.width, r.height);
}

void Canvas::rectline(const i32 x, const i32 y, const i32 width,
                      const i32 height) const {
    m_renderer->rectOutline(x, y, width, height);
}

void Canvas::rectLine(const Point2I p1, const i32 width,
                      const i32 height) const {
    m_renderer->rectOutline(p1.x, p1.y, width, height);
}

void Canvas::rectLine(const Point2I p1, const Point2I p2) const {
    m_renderer->rectOutline(p1.x, p1.y, p2.x - p1.x, p2.y - p1.y);
}

void Canvas::rectLine(const Rect2I r) const {
    m_renderer->rectOutline(r.x, r.y, r.width, r.height);
}

void Canvas::circle(const i32 x, const i32 y, const i32 radius) const {
    m_renderer->circleFill(x, y, radius);
}

void Canvas::circle(const Point2I p, const i32 radius) const {
    m_renderer->circleFill(p.x, p.y, radius);
}

void Canvas::circleline(const i32 x, const i32 y, const i32 radius) const {
    m_renderer->circleOutline(x, y, radius);
}

void Canvas::circleline(const Point2I p, const i32 radius) const {
    m_renderer->circleOutline(p.x, p.y, radius);
}
