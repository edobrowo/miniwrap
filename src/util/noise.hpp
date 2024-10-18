#pragma once

#include <optional>

#include "common.hpp"
#include "math.hpp"

namespace noise {

/// @brief Perlin noise.
/// @note Resources used:
/// - [Understanding Perlin Noise by Adrian
/// Biagioli](https://adrianb.io/2014/08/09/perlinnoise.html)
/// - [Improved Noise reference implementation by Ken
/// Perlin](https://mrl.cs.nyu.edu/~perlin/noise/)
class Perlin {
public:
    /// @brief Uses Ken Perlin's original hash LUT for gradient vectors.
    Perlin() = default;

    /// @brief Determines the 3-D Perlin noise value for the given vector.
    /// @param x x-component.
    /// @param y y-component.
    /// @param z z-component.
    /// @return noise value.
    f64 gen(const f64 x, const f64 y, const f64 z) const {
        // Pseudo-randomly generate gradient vectors at each vertex. The
        // gradient vector is determined by hashing the input vector. The index
        // into the pseudo-random hash permutation is given by the integral part
        // of each component mod 256.
        const u8 xi = static_cast<u8>(static_cast<i64>(std::floor(x)) & 255);
        const u8 yi = static_cast<u8>(static_cast<i64>(std::floor(y)) & 255);
        const u8 zi = static_cast<u8>(static_cast<i64>(std::floor(z)) & 255);

        const u8 x0y0z0 = p[p[p[xi] + yi] + zi];
        const u8 x0y1z0 = p[p[p[xi] + yi + 1] + zi];
        const u8 x0y0z1 = p[p[p[xi] + yi] + zi + 1];
        const u8 x0y1z1 = p[p[p[xi] + yi + 1] + zi + 1];
        const u8 x1y0z0 = p[p[p[xi + 1] + yi] + zi];
        const u8 x1y1z0 = p[p[p[xi + 1] + yi + 1] + zi];
        const u8 x1y0z1 = p[p[p[xi + 1] + yi] + zi + 1];
        const u8 x1y1z1 = p[p[p[xi + 1] + yi + 1] + zi + 1];

        // The fractional component indicates a point within the unit cube.
        const f64 xf = x - std::floor(x);
        const f64 yf = y - std::floor(y);
        const f64 zf = z - std::floor(z);

        // Apply easing to smoothly transition between gradient values.
        const f64 u = fade(xf);
        const f64 v = fade(yf);
        const f64 w = fade(zf);

        // The hash is used to dot a particular distance vector and gradient
        // vector pair. Then trilinearly interpolate between the 8 values.
        const f64 x1 =
            lerp(u, grad(x0y0z0, xf, yf, zf), grad(x1y0z0, xf - 1.0, yf, zf));
        const f64 x2 = lerp(u, grad(x0y1z0, xf, yf - 1.0, zf),
                            grad(x1y1z0, xf - 1.0, yf - 1.0, zf));
        const f64 y1 = lerp(v, x1, x2);

        const f64 x3 = lerp(u, grad(x0y0z1, xf, yf, zf - 1.0),
                            grad(x1y0z1, xf - 1.0, yf, zf - 1.0));
        const f64 x4 = lerp(u, grad(x0y1z1, xf, yf - 1.0, zf - 1.0),
                            grad(x1y1z1, xf - 1.0, yf - 1.0, zf - 1.0));
        const f64 y2 = lerp(v, x3, x4);

        return (lerp(w, y1, y2) + 1) / 2;
    }

    /// @brief Determines the 1-D Perlin noise value for the given vector.
    /// @param x x-component.
    /// @return noise value.
    f64 gen(const f64 x) const { return gen(x, 0.0, 0.0); }

    /// @brief Determines the 2-D Perlin noise value for the given vector.
    /// @param x x-component.
    /// @param y y-component.
    /// @return noise value.
    f64 gen(const f64 x, const f64 y) const { return gen(x, y, 0.0); }

    /// @brief Generate layered octaves of 3-D Perlin noise.
    /// @param x x-component.
    /// @param y y-component.
    /// @param z z-component.
    /// @param octaves Number of octaves to layer.
    /// @param persistence Scalar applied to each successive layer.
    /// @return Perlin noise value.
    f64 octave(const f64 x, const f64 y, const f64 z, const u64 octaves,
               const f64 persistence) const {
        f64 total = 0;
        f64 frequency = 1;
        f64 amplitude = 1;
        f64 max = 0;

        for (u64 i = 0; i < octaves; ++i) {
            total +=
                amplitude * gen(x * frequency, y * frequency, z * frequency);
            max += amplitude;
            amplitude *= persistence;
            frequency *= 2;
        }

        return max > 0.0 ? total / max : 0.0;
    }

private:
    /// @brief Apply the spline 6t^5 - 15t^4 + 10t^3.
    /// @param t value.
    /// @return result.
    static f64 fade(const f64 t) { return t * t * t * (t * (t * 6 - 15) + 10); }

    /// @brief Computes the dot product between a hashed distance vector and an
    /// edge vector. Distance vectors refer to vectors from each corner of the
    /// unit cube to the point within the unit cube. Gradient vectors are simply
    /// one of the 12 edge vectors, i.e., a vector from the center of the cube
    /// to one of center of an edge.
    /// @param hash hashed
    /// @param x Distance vector x-component.
    /// @param y Distance vector y-component.
    /// @param z Distance vector z-component.
    /// @return Gradient value.
    static f64 grad(const i64 hash, const f64 x, const f64 y, const f64 z) {
        switch (hash & 0xF) {
        case 0x0:
            return x + y;
        case 0x1:
            return -x + y;
        case 0x2:
            return x - y;
        case 0x3:
            return -x - y;
        case 0x4:
            return x + z;
        case 0x5:
            return -x + z;
        case 0x6:
            return x - z;
        case 0x7:
            return -x - z;
        case 0x8:
            return y + z;
        case 0x9:
            return -y + z;
        case 0xA:
            return y - z;
        case 0xB:
            return -y - z;
        case 0xC:
            return y + x;
        case 0xD:
            return -y + z;
        case 0xE:
            return y - x;
        case 0xF:
            return -y - z;
        default:
            unreachable;
        }
    }

    /// @brief Linearly interpolate between two values.
    /// @param t Parameter.
    /// @param a Lower bound.
    /// @param b Upper bound.
    /// @return Result.
    static f64 lerp(const f64 t, const f64 a, const f64 b) {
        return a + t * (b - a);
    }

    /// @brief Ken Perlin's original hash LUT.
    static constexpr u8 p[256]{
        151, 160, 137, 91,  90,  15,  131, 13,  201, 95,  96,  53,  194, 233,
        7,   225, 140, 36,  103, 30,  69,  142, 8,   99,  37,  240, 21,  10,
        23,  190, 6,   148, 247, 120, 234, 75,  0,   26,  197, 62,  94,  252,
        219, 203, 117, 35,  11,  32,  57,  177, 33,  88,  237, 149, 56,  87,
        174, 20,  125, 136, 171, 168, 68,  175, 74,  165, 71,  134, 139, 48,
        27,  166, 77,  146, 158, 231, 83,  111, 229, 122, 60,  211, 133, 230,
        220, 105, 92,  41,  55,  46,  245, 40,  244, 102, 143, 54,  65,  25,
        63,  161, 1,   216, 80,  73,  209, 76,  132, 187, 208, 89,  18,  169,
        200, 196, 135, 130, 116, 188, 159, 86,  164, 100, 109, 198, 173, 186,
        3,   64,  52,  217, 226, 250, 124, 123, 5,   202, 38,  147, 118, 126,
        255, 82,  85,  212, 207, 206, 59,  227, 47,  16,  58,  17,  182, 189,
        28,  42,  223, 183, 170, 213, 119, 248, 152, 2,   44,  154, 163, 70,
        221, 153, 101, 155, 167, 43,  172, 9,   129, 22,  39,  253, 19,  98,
        108, 110, 79,  113, 224, 232, 178, 185, 112, 104, 218, 246, 97,  228,
        251, 34,  242, 193, 238, 210, 144, 12,  191, 179, 162, 241, 81,  51,
        145, 235, 249, 14,  239, 107, 49,  192, 214, 31,  181, 199, 106, 157,
        184, 84,  204, 176, 115, 121, 50,  45,  127, 4,   150, 254, 138, 236,
        205, 93,  222, 114, 67,  29,  24,  72,  243, 141, 128, 195, 78,  66,
        215, 61,  156, 180,
    };
};

}
