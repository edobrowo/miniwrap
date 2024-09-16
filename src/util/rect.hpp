#ifndef __UTIL_RECT__
#define __UTIL_RECT__

#include "point.hpp"
#include "vec2.hpp"

class Rect {
public:
    Rect(const int x, const int y, const int width, const int height);
    Rect(const int width, const int height);
    Rect(const Rect& other);
    Rect(Rect&& other) noexcept;

    Rect operator=(const Rect& other);
    Rect operator=(Rect&& other) noexcept;

    inline int x() const noexcept { return m_x; }
    inline int y() const noexcept { return m_y; }
    inline int width() const noexcept { return m_width; }
    inline int height() const noexcept { return m_height; }

    inline int top() const noexcept { return m_y; }
    inline int bottom() const noexcept { return m_y + m_height; }
    inline int left() const noexcept { return m_x; }
    inline int right() const noexcept { return m_x + m_width; }

    Point center() const noexcept;

    bool contains(const int x, const int y) const noexcept;
    bool contains(const Point& point) const noexcept;
    bool contains(const Vec2& vec) const noexcept;

    bool surrounds(const int x, const int y) const noexcept;
    bool surrounds(const Point& point) const noexcept;
    bool surrounds(const Vec2& vec) const noexcept;

    Rect transpose() const noexcept;

private:
    int m_x;
    int m_y;
    int m_width;
    int m_height;
};

#endif
