#include "point.hpp"

#include <algorithm>
#include <utility>

#include "math.h"

Point::Point() {
    m_components[0] = 0;
    m_components[1] = 0;
}

Point::Point(const int x, const int y) {
    m_components[0] = x;
    m_components[1] = y;
}

Point::Point(const Point& other) {
    m_components[0] = other.x();
    m_components[1] = other.y();
}

Point::Point(const Vec2& vec) {
    m_components[0] = static_cast<int>(std::floor(vec.x()));
    m_components[1] = static_cast<int>(std::floor(vec.y()));
}

Point::Point(Point&& other) noexcept {
    m_components[0] = std::move(other.x());
    m_components[1] = std::move(other.y());
}

Point Point::operator=(const Point& other) {
    m_components[0] = other.x();
    m_components[1] = other.y();
    return *this;
}

Point Point::operator=(Point&& other) {
    m_components[0] = std::move(other.x());
    m_components[1] = std::move(other.y());
    return *this;
}

int& Point::operator[](const int index) { return m_components[index]; }

void Point::setX(const int x) noexcept { m_components[0] = x; }

void Point::setY(const int y) noexcept { m_components[1] = y; }

Point Point::transposed() const noexcept { return Point(y(), x()); }

float Point::distEuclidean() const noexcept {
    return ::sqrt(x() * x() + y() * y());
}

float Point::distEuclidean(const Point& other) const noexcept {
    return ::sqrt((x() - other.x()) * (x() - other.x()) +
                  (y() - other.y()) * (y() - other.y()));
}

int Point::distManhattan() const noexcept { return ::abs(x()) + ::abs(y()); }

int Point::distManhattan(const Point& other) const noexcept {
    return ::abs(x() - other.x()) + ::abs(y() - other.y());
}

int Point::distChebyshev() const noexcept {
    return std::max(::abs(x()), ::abs(y()));
}

int Point::distChebyshev(const Point& other) const noexcept {
    return std::max(::abs(x() - other.x()), ::abs(y() - other.y()));
}
