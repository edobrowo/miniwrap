#include "vec2.hpp"

#include <cmath>
#include <utility>

Vec2::Vec2() {
    m_components[0] = 0.0;
    m_components[1] = 0.0;
}

Vec2::Vec2(const float x, const float y) {
    m_components[0] = x;
    m_components[1] = y;
}

Vec2::Vec2(const Vec2& other) {
    m_components[0] = other.x();
    m_components[1] = other.y();
}

Vec2::Vec2(const Point& p) {
    m_components[0] = static_cast<float>(p.x());
    m_components[1] = static_cast<float>(p.y());
}

Vec2::Vec2(Vec2&& other) noexcept {
    m_components[0] = std::move(other.x());
    m_components[1] = std::move(other.y());
}

Vec2 Vec2::operator=(const Vec2& other) {
    m_components[0] = other.x();
    m_components[1] = other.y();
    return *this;
}

Vec2 Vec2::operator=(Vec2&& other) noexcept {
    m_components[0] = std::move(other.x());
    m_components[1] = std::move(other.y());
    return *this;
}

float& Vec2::operator[](const int index) { return m_components[index]; }

void Vec2::setX(const float x) noexcept { m_components[0] = x; }

void Vec2::setY(const float y) noexcept { m_components[1] = y; }

bool Vec2::operator==(const Vec2& rhs) {
    return x() == rhs.x() && y() == rhs.y();
}

Vec2& Vec2::operator+=(const Vec2& rhs) {
    m_components[0] += rhs.x();
    m_components[1] += rhs.y();

    return *this;
}

Vec2& Vec2::operator-=(const Vec2& rhs) {
    m_components[0] -= rhs.x();
    m_components[1] -= rhs.y();

    return *this;
}

Vec2& Vec2::operator*=(const float rhs) {
    m_components[0] *= rhs;
    m_components[1] *= rhs;

    return *this;
}

Vec2& Vec2::operator/=(const float rhs) {
    m_components[0] /= rhs;
    m_components[1] /= rhs;

    return *this;
}

Vec2 Vec2::operator-() const { return Vec2{-x(), -y()}; }

Vec2 Vec2::operator+() const { return Vec2{+x(), +y()}; }

Vec2& Vec2::operator*=(const Vec2& rhs) {
    m_components[0] *= rhs.x();
    m_components[1] *= rhs.y();

    return *this;
}

Vec2& Vec2::operator/=(const Vec2& rhs) {
    m_components[0] /= rhs.x();
    m_components[1] /= rhs.y();

    return *this;
}

float Vec2::dot(const Vec2& other) const noexcept {
    return x() * other.x() + y() * other.y();
}

bool Vec2::isOrthogonal(const Vec2& other) const noexcept {
    return dot(other) == 0;
}

float Vec2::norm() const noexcept { return ::sqrt(dot(*this)); }

float Vec2::length() const noexcept { return norm(); }

Vec2 Vec2::makeUnit() const noexcept {
    float scalar = 1 / norm();
    return Vec2{x() * scalar, y() * scalar};
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
