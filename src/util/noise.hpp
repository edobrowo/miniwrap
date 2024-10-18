#pragma once

#include "common.hpp"
#include "math.hpp"

namespace noise {

// https://adrianb.io/2014/08/09/perlinnoise.html
// https://mrl.cs.nyu.edu/~perlin/noise/
class Perlin {
public:
    using Seed = u64;

    Perlin() = default;
    // TODO: Perlin(const Seed s);

    f64 noise(const f64 x) const { return noise(x, 0.0, 0.0); }

    f64 noise(const f64 x, const f64 y) const { return noise(x, y, 0.0); }

    f64 noise(const f64 x, const f64 y, const f64 z) const {
        const u8 xi = static_cast<u8>(static_cast<i64>(std::floor(x)) & 255);
        const u8 yi = static_cast<u8>(static_cast<i64>(std::floor(y)) & 255);
        const u8 zi = static_cast<u8>(static_cast<i64>(std::floor(z)) & 255);

        const f64 xf = x - std::floor(x);
        const f64 yf = y - std::floor(y);
        const f64 zf = z - std::floor(z);

        const f64 u = Perlin::fade(xf);
        const f64 v = Perlin::fade(yf);
        const f64 w = Perlin::fade(zf);

        const u8 aaa = p[p[p[xi] + yi] + zi];
        const u8 aba = p[p[p[xi] + yi + 1] + zi];
        const u8 aab = p[p[p[xi] + yi] + zi + 1];
        const u8 abb = p[p[p[xi] + yi + 1] + zi + 1];
        const u8 baa = p[p[p[xi + 1] + yi] + zi];
        const u8 bba = p[p[p[xi + 1] + yi + 1] + zi];
        const u8 bab = p[p[p[xi + 1] + yi] + zi + 1];
        const u8 bbb = p[p[p[xi + 1] + yi + 1] + zi + 1];

        const f64 x1 = Perlin::lerp(u, Perlin::grad(aaa, xf, yf, zf),
                                    Perlin::grad(baa, xf - 1.0, yf, zf));
        const f64 x2 = Perlin::lerp(u, Perlin::grad(aba, xf, yf - 1.0, zf),
                                    Perlin::grad(bba, xf - 1.0, yf - 1.0, zf));
        const f64 y1 = Perlin::lerp(v, x1, x2);

        const f64 x3 = Perlin::lerp(u, Perlin::grad(aab, xf, yf, zf - 1.0),
                                    Perlin::grad(bab, xf - 1.0, yf, zf - 1.0));
        const f64 x4 =
            Perlin::lerp(u, Perlin::grad(abb, xf, yf - 1.0, zf - 1.0),
                         Perlin::grad(bbb, xf - 1.0, yf - 1.0, zf - 1.0));
        const f64 y2 = Perlin::lerp(v, x3, x4);

        return (Perlin::lerp(w, y1, y2) + 1) / 2;
    }

private:
    static f64 fade(const f64 t) { return t * t * t * (t * (t * 6 - 15) + 10); }

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

    static f64 lerp(const f64 t, const f64 a, const f64 b) {
        return a + t * (b - a);
    }

    // clang-format off
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
    // clang-format on
};

}
