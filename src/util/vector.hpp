#pragma once

#include "common.hpp"
#include "format.hpp"
#include "math.hpp"
#include "tuple.hpp"

// Based on www.pbr-book.org/4ed/Geometry_and_Transformations/Vectors
template <Numeric N>
class Vector2 : public Tuple2<Vector2, N> {
public:
    using Tuple2<Vector2, N>::x;
    using Tuple2<Vector2, N>::y;

    Vector2() = default;
    Vector2(N x, N y) : Tuple2<Vector2, N>(x, y) {}

    template <Numeric M>
    explicit Vector2(Vector2<M> other) : Tuple2<Vector2, N>(other) {}

    N lengthSquared() const { return x * x + y * y; }

    template <Numeric LengthType>
    struct Length {
        using Type = f32;
    };

    template <>
    struct Length<f64> {
        using Type = f64;
    };

    Length<N>::Type length() const { return std::sqrt(lengthSquared()); }

    inline N dot(Vector2<N> other) const { return x * other.x + y * other.y; }
};

template <Numeric N>
class Vector3 : public Tuple3<Vector3, N> {
public:
    using Tuple3<Vector3, N>::x;
    using Tuple3<Vector3, N>::y;
    using Tuple3<Vector3, N>::z;

    Vector3() = default;
    Vector3(N x, N y, N z) : Tuple3<Vector3, N>(x, y, z) {}

    template <Numeric M>
    explicit Vector3(Vector3<M> other) : Tuple3<Vector3, N>(other) {}

    N lengthSquared() const { return x * x + y * y + z * z; }

    template <Numeric LengthType>
    struct Length {
        using Type = f32;
    };

    template <>
    struct Length<f64> {
        using Type = f64;
    };

    Length<N>::Type length() const { return std::sqrt(lengthSquared()); }

    inline N dot(Vector3<N> other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    inline Vector3<N> cross(Vector3<N> other) const {
        return {
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x,
        };
    }
};

using Vector2D = Vector2<f64>;
using Vector2I = Vector2<i32>;
using Vector3D = Vector3<f64>;
using Vector3I = Vector3<i32>;

template <Numeric N>
    requires FormatWritable<N>
struct FormatWriter<Vector2<N>> {
    static void write(const Vector2<N>& value, StringBuffer& sb) {
        format(sb, "({},{})", value.x, value.y);
    }
};

template <Numeric N>
    requires FormatWritable<N>
struct FormatWriter<Vector3<N>> {
    static void write(const Vector3<N>& value, StringBuffer& sb) {
        format(sb, "({},{},{})", value.x, value.y, value.z);
    }
};
