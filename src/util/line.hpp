#ifndef __UTIL_LINE__
#define __UTIL_LINE__

#include "point.hpp"

class Line {
public:
    Line(const int x1, const int y1, const int x2, const int y2);
    Line(const Point& p1, const Point& p2);
    Line(const Line& other);
    Line(Line&& other) noexcept;

    Line operator=(const Line& other);
    Line operator=(Line&& other) noexcept;

    inline int x1() const noexcept { return m_x1; }
    inline int y1() const noexcept { return m_y1; }
    inline int x2() const noexcept { return m_x2; }
    inline int y2() const noexcept { return m_y2; }

private:
    int m_x1;
    int m_y1;
    int m_x2;
    int m_y2;
};

#endif
