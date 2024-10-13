#pragma once

#include "common.hpp"
#include "point.hpp"
#include "tuple.hpp"
#include "vector.hpp"

template <Numeric N>
class RGB : public Tuple3<RGB, N> {
public:
    using Tuple3<RGB, N>::x;
    using Tuple3<RGB, N>::y;
    using Tuple3<RGB, N>::z;

    RGB() = default;
    RGB(const N r, const N g, const N b) : Tuple3<RGB, N>(r, g, b) {}
    RGB(const N grey) : Tuple3<RGB, N>(grey, grey, grey) {}

    template <Numeric M>
    explicit RGB(RGB<M> other) : Tuple3<RGB, N>(other) {}

    N r() const { return x; }
    N g() const { return y; }
    N b() const { return z; }
};

class RGB24;

class RGBf : public RGB<f64> {
public:
    using RGB<f64>::x;
    using RGB<f64>::y;
    using RGB<f64>::z;

    RGBf() = default;
    RGBf(const f64 r, const f64 g, const f64 b) : RGB<f64>(r, g, b) {}
    RGBf(const f64 grey) : RGB<f64>(grey, grey, grey) {}
    RGBf(const RGB24& rgb24);
};

class RGB24 : public RGB<u8> {
public:
    using RGB<u8>::x;
    using RGB<u8>::y;
    using RGB<u8>::z;

    RGB24() = default;
    RGB24(const u8 r, const u8 g, const u8 b) : RGB<u8>(r, g, b) {}
    RGB24(const u8 grey) : RGB<u8>(grey, grey, grey) {}
    RGB24(const RGBf& rgbf);
};

using Color = RGBf;
