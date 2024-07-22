#ifndef __RECT__
#define __RECT__

#include "point.hpp"

class Rect {
public:
    Rect(const int x, const int y, const int width, const int height);
    Rect(const int width, const int height);
    Rect(const Rect& other);
    Rect(Rect&& other) noexcept;

    Rect operator=(const Rect& other);
    Rect operator=(Rect&& other) noexcept;

    int x() const noexcept;
    int y() const noexcept;
    int width() const noexcept;
    int height() const noexcept;

    int top() const noexcept;
    int bottom() const noexcept;
    int left() const noexcept;
    int right() const noexcept;
    Point center() const noexcept;

    bool contains(const int x, const int y) const noexcept;
    bool contains(const Point& point) const noexcept;
    bool surrounds(const int x, const int y) const noexcept;
    bool surrounds(const Point& point) const noexcept;

    Rect transpose() const noexcept;

private:
    int m_x;
    int m_y;
    int m_width;
    int m_height;
};

#endif
