#pragma once

#include "common.hpp"
#include "format.hpp"
#include "point.hpp"
#include "vector.hpp"

template <Numeric N>
class Rect2 {
public:
    N x;
    N y;
    N width;
    N height;

    Rect2(const N x, const N y, const N width, const N height)
        : x{x}, y{y}, width{width}, height{height} {}

    template <Numeric M>
    Rect2(const Rect2<M>& other)
        : x{other.x}, y{other.y}, width{other.width}, height{other.height} {}

    template <Numeric M>
    Rect2<N> operator=(const Rect2<M>& other) {
        x = other.x;
        y = other.y;
        width = other.width;
        height = other.height;
        return *this;
    }

    N top() const { return y; }
    N bottom() const { return y + height; }
    N left() const { return x; }
    N right() const { return x + width; }

    Point2<N> center() const { return {x + width / 2, y + height / 2}; }

    bool contains(const N xp, const N yp) const {
        return left() <= xp && xp <= right() && top() <= yp && yp <= bottom();
    }
    bool contains(const Point2<N>& point) const {
        return contains(point.x, point.y);
    }
    bool contains(const Vector2<N>& vec) const {
        return contains(vec.x, vec.y);
    }

    bool surrounds(const N xp, const N yp) const {
        return left() < xp && xp < right() && top() < yp && yp < bottom();
    }
    bool surrounds(const Point2<N>& point) const {
        return surrounds(point.x, point.y);
    }
    bool surrounds(const Vector2<N>& vec) const {
        return surrounds(vec.x, vec.y);
    }

    Rect2<N> transpose() const;
};

using Rect2D = Rect2<f64>;
using Rect2I = Rect2<i32>;

template <Numeric N>
    requires FormatWritable<N>
struct FormatWriter<Rect2<N>> {
    static void write(const Rect2<N>& value, StringBuffer& sb) {
        format(sb, "{{x={},y={},width={},height={}}}", value.x, value.y,
               value.width, value.height);
    }
};
