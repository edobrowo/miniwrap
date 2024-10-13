#include "color.hpp"

#include "math.hpp"

namespace {

u8 rgbf_to_rgb24(const f64 channel) { return math::unit_clamp(channel) * 255; }

f64 rgb24_to_rgbf(const u8 channel) { return static_cast<f64>(channel / 255); }

}

RGBf::RGBf(const RGB24& rgb24) {
    this->x = rgb24_to_rgbf(rgb24.r());
    this->y = rgb24_to_rgbf(rgb24.g());
    this->z = rgb24_to_rgbf(rgb24.b());
}

RGB24::RGB24(const RGBf& rgbf) {
    this->x = rgbf_to_rgb24(rgbf.r());
    this->y = rgbf_to_rgb24(rgbf.g());
    this->z = rgbf_to_rgb24(rgbf.b());
}
