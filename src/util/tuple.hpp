#pragma once

#include "common.hpp"
#include "format.hpp"
#include "math.hpp"

// Based on
// www.pbr-book.org/4ed/Geometry_and_Transformations/n-Tuple_Base_Classes
template <template <Numeric> typename Child, Numeric N>
class Tuple2 {
public:
    N x, y;

    static constexpr u32 DIMS = 2;

    Tuple2() = default;
    Tuple2(N x, N y) : x(x), y(y) {}
    Tuple2(Child<N> child) : x(child.x), y(child.y) {}
    Child<N>& operator=(Child<N> other) {
        x = other.x;
        y = other.y;
        return static_cast<Child<N>&>(*this);
    }

    bool operator==(Child<N> other) const {
        return x == other.x && y == other.y;
    }

    bool operator!=(Child<N> other) const {
        return x != other.x || y != other.y;
    }

    Child<N> operator-() const { return {-x, -y}; }

    template <Numeric M>
    Child<decltype(N{} + M{})> operator+(Child<M> other) const {
        return {x + other.x, y + other.y};
    }
    template <Numeric M>
    Child<N>& operator+=(Child<M> other) {
        x += other.x;
        y += other.y;
        return static_cast<Child<N>&>(*this);
    }

    template <Numeric M>
    Child<decltype(N{} - M{})> operator-(Child<M> other) const {
        return {x - other.x, y - other.y};
    }
    template <Numeric M>
    Child<N>& operator-=(Child<M> other) {
        x -= other.x;
        y -= other.y;
        return static_cast<Child<N>&>(*this);
    }

    template <Numeric S>
    Child<decltype(S{} * N{})> operator*(S scalar) const {
        return {scalar * x, scalar * y};
    }
    template <Numeric S>
    friend Child<decltype(N{} * S{})> operator*(S scalar,
                                                Tuple2<Child, N> tuple) {
        return tuple *= scalar;
    }
    template <Numeric S>
    Child<decltype(N{} * S{})>& operator*=(S scalar) {
        x *= scalar;
        y *= scalar;
        return static_cast<Child<N>&>(*this);
    }

    template <Numeric S>
    Child<decltype(S{} / N{})> operator/(S scalar) const {
        assert(scalar != 0);
        return {x / scalar, y / scalar};
    }
    template <Numeric S>
    friend Child<decltype(N{} / S{})> operator/(S scalar,
                                                Tuple2<Child, N> tuple) {
        return tuple /= scalar;
    }
    template <Numeric S>
    Child<decltype(S{} / N{})>& operator/=(S scalar) {
        assert(scalar != 0);
        x /= scalar;
        y /= scalar;
        return static_cast<Child<N>&>(*this);
    }

    template <Numeric M>
    Child<decltype(N{} * M{})> operator*(Child<M> other) const {
        return {x * other.x, y * other.y};
    }
    template <Numeric M>
    Child<N>& operator*=(Child<M> other) {
        x *= other.x;
        y *= other.y;
        return static_cast<Child<N>&>(*this);
    }

    template <Numeric M>
    Child<decltype(N{} / M{})> operator/(Child<M> other) const {
        assert(other.x != 0);
        assert(other.y != 0);
        return {x / other.x, y / other.y};
    }
    template <Numeric M>
    Child<N>& operator/=(Child<M> other) {
        x /= other.x;
        y /= other.y;
        return static_cast<Child<N>&>(*this);
    }
};

template <template <Numeric> typename Child, Numeric N>
inline Child<N> min(Tuple2<Child, N> a, Tuple2<Child, N> b) {
    return {std::min(a.x, b.x), std::min(a.y, b.y)};
}

template <template <Numeric> typename Child, Numeric N>
inline Child<N> max(Tuple2<Child, N> a, Tuple2<Child, N> b) {
    return {std::max(a.x, b.x), std::max(a.y, b.y)};
}

template <template <Numeric> typename Child, Numeric N>
class Tuple3 {
public:
    N x, y, z;

    static constexpr u32 DIMS = 3;

    Tuple3() = default;
    Tuple3(N x, N y, N z) : x(x), y(y), z(z) {}
    Tuple3(Child<N> child) : x(child.x), y(child.y), z(child.z) {}
    Child<N>& operator=(Child<N> other) {
        x = other.x;
        y = other.y;
        z = other.z;
        return static_cast<Child<N>&>(*this);
    }

    bool operator==(Child<N> other) const {
        return x == other.x && y == other.y && z == other.z;
    }

    bool operator!=(Child<N> other) const {
        return x != other.x || y != other.y || z != other.z;
    }

    Child<N> operator-() const { return {-x, -y, -z}; }

    template <Numeric M>
    Child<decltype(N{} + M{})> operator+(Child<M> other) const {
        return {x + other.x, y + other.y, z + other.z};
    }
    template <Numeric M>
    Child<N>& operator+=(Child<M> other) {
        x += other.x;
        y += other.y;
        z += other.z;
        return static_cast<Child<N>&>(*this);
    }

    template <Numeric M>
    Child<decltype(N{} - M{})> operator-(Child<M> other) const {
        return {x - other.x, y - other.y, z - other.z};
    }
    template <Numeric M>
    Child<N>& operator-=(Child<M> other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return static_cast<Child<N>&>(*this);
    }

    template <Numeric S>
    Child<decltype(S{} * N{})> operator*(S scalar) const {
        return {scalar * x, scalar * y, scalar * z};
    }
    template <Numeric S>
    friend Child<decltype(N{} * S{})> operator*(S scalar,
                                                Tuple3<Child, N> tuple) {
        return tuple *= scalar;
    }
    template <Numeric S>
    Child<decltype(N{} * S{})>& operator*=(S scalar) {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return static_cast<Child<N>&>(*this);
    }

    template <Numeric S>
    Child<decltype(S{} / N{})> operator/(S scalar) const {
        assert(scalar != 0);
        return {x / scalar, y / scalar, z / scalar};
    }
    template <Numeric S>
    friend Child<decltype(N{} / S{})> operator/(S scalar,
                                                Tuple3<Child, N> tuple) {
        return tuple /= scalar;
    }
    template <Numeric S>
    Child<decltype(S{} / N{})>& operator/=(S scalar) {
        assert(scalar != 0);
        x /= scalar;
        y /= scalar;
        z /= scalar;
        return static_cast<Child<N>&>(*this);
    }

    template <Numeric M>
    Child<decltype(N{} * M{})> operator*(Child<M> other) const {
        return {x * other.x, y * other.y, z * other.z};
    }
    template <Numeric M>
    Child<N>& operator*=(Child<M> other) {
        x *= other.x;
        y *= other.y;
        z *= other.z;
        return static_cast<Child<N>&>(*this);
    }

    template <Numeric M>
    Child<decltype(N{} / M{})> operator/(Child<M> other) const {
        assert(other.x != 0);
        assert(other.y != 0);
        assert(other.z != 0);
        return {x / other.x, y / other.y, z / other.z};
    }
    template <Numeric M>
    Child<N>& operator/=(Child<M> other) {
        assert(other.x != 0);
        assert(other.y != 0);
        assert(other.z != 0);
        x /= other.x;
        y /= other.y;
        z /= other.z;
        return static_cast<Child<N>&>(*this);
    }
};

template <template <Numeric> typename Child, Numeric N>
inline Child<N> min(Tuple3<Child, N> a, Tuple3<Child, N> b) {
    return {std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z)};
}

template <template <Numeric> typename Child, Numeric N>
inline Child<N> max(Tuple3<Child, N> a, Tuple3<Child, N> b) {
    return {std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z)};
}

template <template <Numeric> typename Child, Numeric N>
    requires FormatWritable<N>
struct FormatWriter<Tuple2<Child, N>> {
    static void write(const Tuple2<Child, N>& value, StringBuffer& sb) {
        format(sb, "({},{})", value.x, value.y);
    }
};

template <template <Numeric> typename Child, Numeric N>
    requires FormatWritable<N>
struct FormatWriter<Tuple3<Child, N>> {
    static void write(const Tuple3<Child, N>& value, StringBuffer& sb) {
        format(sb, "({},{},{})", value.x, value.y, value.z);
    }
};
