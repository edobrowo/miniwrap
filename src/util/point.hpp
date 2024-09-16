#ifndef __UTIL_POINT__
#define __UTIL_POINT__

#include "vec2.hpp"

class Vec2;

class Point {
public:
    Point();
    Point(const int x, const int y);
    Point(const Point& other);
    explicit Point(const Vec2& vec);
    Point(Point&& other) noexcept;

    Point operator=(const Point& other);
    Point operator=(Point&& other);

    int& operator[](const int index);

    inline int x() const noexcept { return m_components[0]; }
    inline int y() const noexcept { return m_components[1]; }

    void setX(const int x) noexcept;
    void setY(const int y) noexcept;

    Point transposed() const noexcept;

    float distEuclidean() const noexcept;
    float distEuclidean(const Point& other) const noexcept;

    int distManhattan() const noexcept;
    int distManhattan(const Point& other) const noexcept;

    int distChebyshev() const noexcept;
    int distChebyshev(const Point& other) const noexcept;

private:
    int m_components[2];
};

#endif
