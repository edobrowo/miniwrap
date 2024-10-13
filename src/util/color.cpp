#include "color.hpp"

namespace {

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

}

Color::Color(const float r, const float g, const float b) {
    m_channels[0] = unit_clamp(r);
    m_channels[1] = unit_clamp(g);
    m_channels[2] = unit_clamp(b);
    m_channels[3] = 1.0;
}

Color::Color(const float r, const float g, const float b, const float a) {
    m_channels[0] = unit_clamp(r);
    m_channels[1] = unit_clamp(g);
    m_channels[2] = unit_clamp(b);
    m_channels[3] = unit_clamp(a);
}

Color::Color(const int r, const int g, const int b) {
    m_channels[0] = unit_clamp(r);
    m_channels[1] = unit_clamp(g);
    m_channels[2] = unit_clamp(b);
    m_channels[3] = 1.0;
}

Color::Color(const int r, const int g, const int b, const int a) {
    m_channels[0] = unit_clamp(r);
    m_channels[1] = unit_clamp(g);
    m_channels[2] = unit_clamp(b);
    m_channels[3] = unit_clamp(a);
}

Color::Color(const Color& other) {
    m_channels[0] = other.r();
    m_channels[1] = other.g();
    m_channels[2] = other.b();
    m_channels[3] = other.a();
}

Color Color::operator=(const Color& other) {
    m_channels[0] = other.r();
    m_channels[1] = other.g();
    m_channels[2] = other.b();
    m_channels[3] = other.a();
    return *this;
}

float& Color::operator[](const int index) { return m_channels[index]; }
