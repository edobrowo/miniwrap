#pragma once

#include <cmath>

#include "common.hpp"

namespace math {

constexpr f64 Pi = 3.14159265358979323846;
constexpr f64 PiH = 1.57079632679489661923;
constexpr f64 PiQ = 0.78539816339744830961;
constexpr f64 InvPi = 0.31830988618379067154;
constexpr f64 Tau = 6.28318530717958647692;
constexpr f64 InvTau = 0.15915494309189533577;

template <Numeric N>
constexpr inline N step(N value, N threshold) {
    return value < threshold ? 0 : 1;
}

template <Numeric N>
constexpr inline N clamp(N value, N left, N right) {
    if (value < left)
        return left;
    else if (value > right)
        return right;
    return value;
}

template <std::floating_point F>
constexpr inline F unit_clamp(F value) {
    if (value < 0.0)
        return 0.0;
    else if (value > 1.0)
        return 1.0;
    return value;
}

template <std::floating_point F>
constexpr inline F lerp(F a, F b, F t) {
    return t * a + (1.0 - t) * b;
}

template <Numeric N>
constexpr inline N scale(N value, N min, N max) {
    assert(max - min != 0);
    return (value - min) / (max - min);
}

template <Numeric N>
constexpr inline N map(N value, N min1, N max1, N min2, N max2) {
    assert(max1 - min1 != 0);
    return min2 + (value - min1) * (max2 - min2) / (max1 - min1);
}

template <Numeric N>
constexpr inline N hermite(N value) {
    return value * value * (3.0 - 2.0 * value);
}

template <Numeric N>
constexpr inline N smoothstep(N left, N right, N t) {
    return hermite(clamp(scale(t, left, right)));
}

}
