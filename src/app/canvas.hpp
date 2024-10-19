#pragma once

#include <memory>

#include "point.hpp"
#include "rect.hpp"
#include "renderer.hpp"

class Canvas {
public:
    Canvas() = default;

    void init(Renderer* renderer, const Size width, const Size height);

    Size width() const;
    Size height() const;

    void setColor(const Color& c) const;

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
    void rectLine(const Point2I p1, const i32 width, const i32 height) const;
    void rectLine(const Point2I p1, const Point2I p2) const;
    void rectLine(const Rect2I r) const;

    void circle(const i32 x, const i32 y, const i32 radius) const;
    void circle(const Point2I p, const i32 radius) const;

    void circleline(const i32 x, const i32 y, const i32 radius) const;
    void circleline(const Point2I p, const i32 radius) const;

private:
    Renderer* m_renderer;
    Size m_width;
    Size m_height;
};
