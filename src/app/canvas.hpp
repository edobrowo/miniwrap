#pragma once

#include <memory>

#include "point.hpp"
#include "rect.hpp"
#include "renderer.hpp"

class Canvas {
public:
    Canvas() = default;

    void init(Renderer* renderer, const u32 width, const u32 height);

    u32 width() const;
    u32 height() const;

    void setColor(const Color& c) const;

    void fill(const Color& c) const;

    void pixel(const i32 x, const i32 y) const;
    void pixel(const Point2I p) const;
    void pixels(const std::vector<Point2I>& points) const;

    void line(const i32 x1, const i32 y1, const i32 x2, const i32 y2) const;
    void line(const Point2I p1, const Point2I p2) const;
    void line(const Rect2I r) const;
    void polyline(const std::vector<Point2I>& points) const;

    void rect(const i32 x, const i32 y, const i32 width,
              const i32 height) const;
    void rect(const Point2I p1, const i32 width, const i32 height) const;
    void rect(const Point2I p1, const Point2I p2) const;
    void rect(const Rect2I r) const;

    void rectline(const i32 x, const i32 y, const i32 width,
                  const i32 height) const;
    void rectline(const Point2I p1, const i32 width, const i32 height) const;
    void rectline(const Point2I p1, const Point2I p2) const;
    void rectline(const Rect2I r) const;

    void circle(const i32 x, const i32 y, const i32 radius) const;
    void circle(const Point2I p, const i32 radius) const;
    void circles(const std::vector<Point2I>& centers, const i32 radius) const;

    void circleline(const i32 x, const i32 y, const i32 radius) const;
    void circleline(const Point2I p, const i32 radius) const;

    void cubicSplineCurve(const std::vector<Point2I>& points,
                          const u32 divisions = 20) const;

private:
    Renderer* m_renderer;
    u32 m_width;
    u32 m_height;
};
