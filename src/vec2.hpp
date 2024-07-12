#ifndef __VEC2__
#define __VEC2__

class Vec2 {
public:
    Vec2();

    Vec2(const float x, const float y);
    Vec2(const int x, const int y);

    Vec2(const Vec2& other);
    Vec2 operator=(const Vec2& other);
    Vec2(Vec2&& other) noexcept;
    Vec2 operator=(Vec2&& other) noexcept;

    float x() const noexcept;
    float y() const noexcept;

private:
    float m_x;
    float m_y;
};

#endif
