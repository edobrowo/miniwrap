#pragma once

class Color {
public:
    Color() = default;
    Color(const float r, const float g, const float b);
    Color(const float r, const float g, const float b, const float a);
    Color(const int r, const int g, const int b);
    Color(const int r, const int g, const int b, const int a);
    Color(const Color& other);
    Color operator=(const Color& other);

    float& operator[](const int index);

    // Channel access
    inline float r() const noexcept { return m_channels[0]; }
    inline float g() const noexcept { return m_channels[1]; }
    inline float b() const noexcept { return m_channels[2]; }
    inline float a() const noexcept { return m_channels[3]; }

private:
    float m_channels[4];
};
