#pragma once

#include "common.hpp"

struct FrameInfo {
    u64 frame;
    u64 ms;
    u64 fps;

    u64 mspf() const { return 1000 / fps; }
    u64 sec() const { return ms / 1000; }
};
