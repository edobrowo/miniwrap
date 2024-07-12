#include "color.hpp"

float unit_clamp(const float x) {
    if (x < 0.0)
        return 0.0;
    else if (x > 1.0)
        return 1.0;
    return x;
}

float unit_clamp(const int x) {
    float y = static_cast<float>(x);
    if (y < 0.0)
        y = 0.0;
    else if (y > 255.0)
        return 255.0;
    return y / 255.0;
}

Color::Color() : m_red{0.0}, m_green{0.0}, m_blue{0.0}, m_alpha{1.0} {}

Color::Color(const float r, const float g, const float b)
    : m_red{unit_clamp(r)}, m_green{unit_clamp(g)}, m_blue{unit_clamp(b)}, m_alpha{1.0} {}

Color::Color(const float r, const float g, const float b, const float a)
    : m_red{unit_clamp(r)}, m_green{unit_clamp(g)}, m_blue{unit_clamp(b)}, m_alpha{unit_clamp(a)} {}

Color::Color(const int r, const int g, const int b)
    : m_red{unit_clamp(r)}, m_green{unit_clamp(g)}, m_blue{unit_clamp(b)}, m_alpha{1.0} {}

Color::Color(const int r, const int g, const int b, const int a)
    : m_red{unit_clamp(r)}, m_green{unit_clamp(g)}, m_blue{unit_clamp(b)}, m_alpha{unit_clamp(a)} {}

Color::Color(const Color& other)
    : m_red{other.m_red}, m_green{other.m_green}, m_blue{other.m_blue}, m_alpha{other.m_alpha} {}

Color Color::operator=(const Color& other) {
    return Color(other);
}

Color::Color(Color&& other) noexcept
    : m_red{other.m_red}, m_green{other.m_green}, m_blue{other.m_blue}, m_alpha{other.m_alpha} {}

Color Color::operator=(Color&& other) noexcept {
    return Color(other);
}

float Color::r() const noexcept {
    return m_red;
}

float Color::g() const noexcept {
    return m_green;
}

float Color::b() const noexcept {
    return m_blue;
}

float Color::a() const noexcept {
    return m_alpha;
}
