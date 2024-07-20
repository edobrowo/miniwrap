#include "vec2.hpp"

#include <cmath>
#include <utility>

Vec2::Vec2() : m_x{0.0}, m_y{0.0} {}

Vec2::Vec2(const float x, const float y) : m_x{x}, m_y{y} {}

Vec2::Vec2(const Vec2& other) : m_x{other.x()}, m_y{other.y()} {}

Vec2 Vec2::operator=(const Vec2& other) {
    m_x = other.x();
    m_y = other.y();

    return *this;
}

Vec2::Vec2(Vec2&& other) noexcept : m_x{std::move(other.x())}, m_y{std::move(other.y())} {}

Vec2 Vec2::operator=(Vec2&& other) noexcept {
    m_x = std::move(other.x());
    m_y = std::move(other.y());

    return *this;
}

float Vec2::x() const noexcept {
    return m_x;
}

float Vec2::y() const noexcept {
    return m_y;
}

bool Vec2::operator==(const Vec2& rhs) {
    return m_x == rhs.x() && m_y == rhs.y();
}

Vec2& Vec2::operator+=(const Vec2& rhs) {
    m_x += rhs.x();
    m_y += rhs.y();

    return *this;
}

Vec2& Vec2::operator-=(const Vec2& rhs) {
    m_x -= rhs.x();
    m_y -= rhs.y();

    return *this;
}

Vec2& Vec2::operator*=(const float rhs) {
    m_x *= rhs;
    m_y *= rhs;

    return *this;
}

Vec2& Vec2::operator/=(const float rhs) {
    m_x /= rhs;
    m_y /= rhs;

    return *this;
}

Vec2 Vec2::operator-() const {
    return Vec2{-m_x, -m_y};
}

Vec2 Vec2::operator+() const {
    return Vec2{+m_x, +m_y};
}

Vec2& Vec2::operator*=(const Vec2& rhs) {
    m_x *= rhs.x();
    m_y *= rhs.y();

    return *this;
}

Vec2& Vec2::operator/=(const Vec2& rhs) {
    m_x /= rhs.x();
    m_y /= rhs.y();

    return *this;
}

float Vec2::dot(const Vec2& other) const noexcept {
    return m_x * other.x() + m_y * other.y();
}

bool Vec2::isOrthogonal(const Vec2& other) const noexcept {
    return dot(other) == 0;
}

float Vec2::norm() const noexcept {
    return ::sqrt(dot(*this));
}

float Vec2::length() const noexcept {
    return norm();
}

Vec2 Vec2::makeUnit() const noexcept {
    float scalar = 1 / norm();
    return Vec2{m_x * scalar, m_y * scalar};
}

float Vec2::distance(const Vec2& other) const noexcept {
    return (*this - other).norm();
}

float Vec2::angle(const Vec2& other) const noexcept {
    return std::acos(dot(other) / norm() * other.norm());
}

Vec2 Vec2::project(const Vec2& other) const noexcept {
    return dot(other) / other.norm() * other.norm() * other;
}
