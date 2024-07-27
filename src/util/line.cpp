#include "line.hpp"

#include <utility>

Line::Line(const int x1, const int y1, const int x2, const int y2) : m_x1{x1}, m_y1{y1}, m_x2{x2}, m_y2{y2} {}

Line::Line(const Point& p1, const Point& p2) : m_x1{p1.x()}, m_y1{p1.y()}, m_x2{p2.x()}, m_y2{p2.y()} {}

Line::Line(const Line& other) : m_x1{other.x1()}, m_y1{other.y1()}, m_x2{other.x2()}, m_y2{other.y2()} {}

Line::Line(Line&& other) noexcept : m_x1{std::move(other.x1())}, m_y1{std::move(other.y1())}, m_x2{std::move(other.x2())}, m_y2{std::move(other.y2())} {}

Line Line::operator=(const Line& other) {
    m_x1 = other.x1();
    m_y1 = other.y1();
    m_x2 = other.x2();
    m_y2 = other.y2();
    return *this;
}

Line Line::operator=(Line&& other) noexcept {
    m_x1 = std::move(other.x1());
    m_y1 = std::move(other.y1());
    m_x2 = std::move(other.x2());
    m_y2 = std::move(other.y2());
    return *this;
}

int Line::x1() const noexcept {
    return m_x1;
}

int Line::y1() const noexcept {
    return m_y1;
}

int Line::x2() const noexcept {
    return m_x2;
}

int Line::y2() const noexcept {
    return m_y2;
}
