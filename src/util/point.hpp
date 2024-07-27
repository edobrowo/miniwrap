#ifndef __UTIL_POINT__
#define __UTIL_POINT__

class Point {
public:
    Point();
    Point(const int x, const int y);
    Point(const Point& other);
    Point(Point&& other) noexcept;

    Point operator=(const Point& other);
    Point operator=(Point&& other);

    int x() const noexcept;
    int y() const noexcept;

    Point transposed() const noexcept;

    float distEuclidean() const noexcept;
    float distEuclidean(const Point& other) const noexcept;

    int distManhattan() const noexcept;
    int distManhattan(const Point& other) const noexcept;

    int distChebyshev() const noexcept;
    int distChebyshev(const Point& other) const noexcept;

private:
    int m_x;
    int m_y;
};

#endif
