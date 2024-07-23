#ifndef __UTIL_VEC2__
#define __UTIL_VEC2__

class Vec2 {
public:
    Vec2();
    Vec2(const float x, const float y);
    Vec2(const Vec2& other);
    Vec2(Vec2&& other) noexcept;

    Vec2 operator=(const Vec2& other);
    Vec2 operator=(Vec2&& other) noexcept;

    // Component access
    float x() const noexcept;
    float y() const noexcept;

    // Equality
    bool operator==(const Vec2& rhs);

    // Vector addition
    Vec2& operator+=(const Vec2& rhs);
    friend Vec2 operator+(Vec2 lhs, const Vec2& rhs) {
        lhs += rhs;
        return lhs;
    }
    Vec2& operator-=(const Vec2& rhs);
    friend Vec2 operator-(Vec2 lhs, const Vec2& rhs) {
        lhs -= rhs;
        return lhs;
    }

    // Scalar multiplication
    Vec2& operator*=(const float rhs);
    friend Vec2 operator*(const float lhs, Vec2 rhs) {
        return rhs *= lhs;
    }
    Vec2& operator/=(const float rhs);
    friend Vec2 operator/(const float lhs, Vec2 rhs) {
        return rhs /= lhs;
    }
    Vec2 operator-() const;
    Vec2 operator+() const;

    // Hadamard product
    Vec2& operator*=(const Vec2& rhs);
    friend Vec2 operator*(Vec2 lhs, const Vec2& rhs) {
        lhs *= rhs;
        return lhs;
    }
    Vec2& operator/=(const Vec2& rhs);
    friend Vec2 operator/(Vec2 lhs, const Vec2& rhs) {
        lhs /= rhs;
        return lhs;
    }

    // Dot product
    float dot(const Vec2& other) const noexcept;

    // Orthogonality check
    bool isOrthogonal(const Vec2& other) const noexcept;

    // Euclidean norm
    float norm() const noexcept;
    float length() const noexcept;

    // Normalization
    Vec2 makeUnit() const noexcept;

    // Distance between vectors
    float distance(const Vec2& other) const noexcept;

    // Angle between vectors
    float angle(const Vec2& other) const noexcept;

    // Projection of this vector onto another vector
    Vec2 project(const Vec2& other) const noexcept;

private:
    float m_x;
    float m_y;
};

#endif
