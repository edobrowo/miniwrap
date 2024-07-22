#include "rect.hpp"

#include <utility>

Rect::Rect(const int x, const int y, const int width, const int height) : m_x{x}, m_y{y}, m_width{width}, m_height{height} {}

Rect::Rect(const int width, const int height) : m_x{0}, m_y{0}, m_width{width}, m_height{height} {}

Rect::Rect(const Rect& other) : m_x{other.x()}, m_y{other.y()}, m_width{other.width()}, m_height{other.height()} {}

Rect::Rect(Rect&& other) : m_x{std::move(other.x())}, m_y{std::move(other.y())}, m_width{std::move(other.width())}, m_height{std::move(other.height())} {}

Rect Rect::operator=(const Rect& other) {
    m_x = other.x();
    m_y = other.y();
    m_width = other.width();
    m_height = other.height();
    return *this;
}

Rect Rect::operator=(Rect&& other) noexcept {
    m_x = std::move(other.x());
    m_y = std::move(other.y());
    m_width = std::move(other.width());
    m_height = std::move(other.height());
    return *this;
}

int Rect::x() const noexcept {
    return m_x;
}

int Rect::y() const noexcept {
    return m_y;
}

int Rect::width() const noexcept {
    return m_width;
}

int Rect::height() const noexcept {
    return m_height;
}

int Rect::top() const noexcept {
    return m_y;
}

int Rect::bottom() const noexcept {
    return m_y + m_height;
}

int Rect::left() const noexcept {
    return m_x;
}

int Rect::right() const noexcept {
    return m_x + m_width;
}

Point Rect::center() const noexcept {
    return Point(m_x + m_width / 2, m_y + m_height / 2);
}

bool Rect::contains(const int x, const int y) const noexcept {
    return left() <= x && x <= right() && top() <= y && y <= bottom();
}

bool Rect::contains(const Point& point) const noexcept {
    return left() <= point.x() && point.x() <= right() && top() <= point.y() && point.y() <= bottom();
}

bool Rect::surrounds(const int x, const int y) const noexcept {
    return left() < x && x < right() && top() < y && y < bottom();
}

bool Rect::surrounds(const Point& point) const noexcept {
    return left() < point.x() && point.x() < right() && top() < point.y() && point.y() < bottom();
}

Rect Rect::transpose() const noexcept {
    return Rect(m_x, m_y, m_height, m_width);
}
