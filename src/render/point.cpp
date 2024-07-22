#include "point.hpp"

#include <algorithm>
#include <utility>

#include "math.h"

Point::Point() : m_x{0}, m_y{0} {}

Point::Point(const int x, const int y) : m_x{x}, m_y{y} {}

Point::Point(const Point& other) : m_x{other.x()}, m_y{other.y()} {}

Point::Point(Point&& other) noexcept : m_x{std::move(other.x())}, m_y{std::move(other.y())} {}

Point Point::operator=(const Point& other) {
    m_x = other.x();
    m_y = other.y();
    return *this;
}

Point Point::operator=(Point&& other) {
    m_x = std::move(other.x());
    m_y = std::move(other.y());
    return *this;
}

int Point::x() const noexcept {
    return m_x;
}

int Point::y() const noexcept {
    return m_y;
}

Point Point::transposed() const noexcept {
    return Point(m_y, m_x);
}

float Point::distEuclidean() const noexcept {
    return ::sqrt(m_x * m_x + m_y * m_y);
}

float Point::distEuclidean(const Point& other) const noexcept {
    return ::sqrt((m_x - other.x()) * (m_x - other.x()) + (m_y - other.y()) * (m_y - other.y()));
}

int Point::distManhattan() const noexcept {
    return ::abs(m_x) + ::abs(m_y);
}

int Point::distManhattan(const Point& other) const noexcept {
    return ::abs(m_x - other.x()) + ::abs(m_y - other.y());
}

int Point::distChebyshev() const noexcept {
    return std::max(::abs(m_x), ::abs(m_y));
}

int Point::distChebyshev(const Point& other) const noexcept {
    return std::max(::abs(m_x - other.x()), ::abs(m_y - other.y()));
}
