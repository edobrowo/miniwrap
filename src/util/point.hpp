#pragma once

#include "common.hpp"
#include "tuple.hpp"
#include "vector.hpp"

// Based on www.pbr-book.org/4ed/Geometry_and_Transformations/Points
template <Numeric N>
class Point2 : public Tuple2<Point2, N> {
public:
    using Tuple2<Point2, N>::x;
    using Tuple2<Point2, N>::y;
    using Tuple2<Point2, N>::operator+;
    using Tuple2<Point2, N>::operator+=;
    using Tuple2<Point2, N>::operator*;
    using Tuple2<Point2, N>::operator*=;

    Point2() = default;
    Point2(N x, N y) : Tuple2<Point2, N>(x, y) {}

    Point2<N> operator-() { return {-x, -y}; }

    template <Numeric M>
    explicit Point2(Point2<M> other)
        : Tuple2<Point2, N>(N(other.x), N(other.y)) {}

    template <Numeric M>
    explicit Point2(Vector2<M> other)
        : Tuple2<Point2, N>(N(other.x), N(other.y)) {}

    template <Numeric M>
    Point2<decltype(N{} + M{})> operator+(Vector2<M> other) const {
        return {x + other.x, y + other.y};
    }
    template <Numeric M>
    Point2<N> operator+=(Vector2<M> other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    template <Numeric M>
    Point2<decltype(N{} - M{})> operator-(Vector2<M> other) const {
        return {x - other.x, y - other.y};
    }
    template <Numeric M>
    Point2<N> operator-=(Vector2<M> other) const {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    template <Numeric M>
    Vector2<decltype(N{} - M{})> operator-(Point2<M> other) const {
        return {x - other.x, y - other.y};
    }
};

template <Numeric N>
class Point3 : public Tuple3<Point3, N> {
public:
    using Tuple3<Point3, N>::x;
    using Tuple3<Point3, N>::y;
    using Tuple3<Point3, N>::z;
    using Tuple3<Point3, N>::operator+;
    using Tuple3<Point3, N>::operator+=;
    using Tuple3<Point3, N>::operator*;
    using Tuple3<Point3, N>::operator*=;

    Point3() = default;
    Point3(N x, N y, N z) : Tuple3<Point3, N>(x, y, z) {}

    Point3<N> operator-() { return {-x, -y, -z}; }

    template <Numeric M>
    explicit Point3(Point3<M> other)
        : Tuple3<Point3, N>(N(other.x), N(other.y), N(other.z)) {}

    template <Numeric M>
    explicit Point3(Vector3<M> other)
        : Tuple3<Point3, N>(N(other.x), N(other.y), N(other.z)) {}

    template <Numeric M>
    Point3<decltype(N{} + M{})> operator+(Vector3<M> other) const {
        return {x + other.x, y + other.y, z + other.z};
    }
    template <Numeric M>
    Point3<N> operator+=(Vector3<M> other) const {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    template <Numeric M>
    Point3<decltype(N{} - M{})> operator-(Vector3<M> other) const {
        return {x - other.x, y - other.y, z - other.z};
    }
    template <Numeric M>
    Point3<N> operator-=(Vector3<M> other) const {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }

    template <Numeric M>
    Vector3<decltype(N{} - M{})> operator-(Point3<M> other) const {
        return {x - other.x, y - other.y, z - other.z};
    }
};

using Point2D = Point2<f64>;
using Point2I = Point2<i32>;
using Point3D = Point3<f64>;
using Point3I = Point3<i32>;

template <Numeric N>
    requires FormatWritable<N>
struct FormatWriter<Point2<N>> {
    static void write(const Point2<N>& value, StringBuffer& sb) {
        format(sb, "({},{})", value.x, value.y);
    }
};

template <Numeric N>
    requires FormatWritable<N>
struct FormatWriter<Point3<N>> {
    static void write(const Point3<N>& value, StringBuffer& sb) {
        format(sb, "({},{},{})", value.x, value.y, value.z);
    }
};
