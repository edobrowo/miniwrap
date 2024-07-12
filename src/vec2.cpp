#include "vec2.hpp"

#include <utility>

Vec2::Vec2() : m_x{0.0}, m_y{0.0} {}

Vec2::Vec2(const float x, const float y) : m_x{x}, m_y{y} {}

Vec2::Vec2(const int x, const int y) : m_x{static_cast<float>(x)}, m_y{static_cast<float>(y)} {}

Vec2::Vec2(const Vec2& other) : m_x{other.x()}, m_y{other.y()} {}

Vec2 Vec2::operator=(const Vec2& other) {
    if (this == &other) {
        return *this;
    }

    m_x = other.x();
    m_y = other.y();

    return *this;
}

Vec2::Vec2(Vec2&& other) noexcept : m_x{std::move(other.x())}, m_y{std::move(other.y())} {}

Vec2 Vec2::operator=(Vec2&& other) noexcept {
    if (this == &other) {
        return *this;
    }

    m_x = std::move(other.x());
    m_y = std::move(other.y());

    return *this;
}
