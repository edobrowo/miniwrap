#pragma once

#include "common.hpp"
#include "event.hpp"
#include "point.hpp"

class MouseMoveEvent : public Event {
public:
    Point2I pos;
    Point2I rel;

    MouseMoveEvent(const u64 timestamp, const i32 x, const i32 y,
                   const i32 rel_x, const i32 rel_y);

    i32 x() const;
    i32 y() const;
    i32 xrel() const;
    i32 yrel() const;
};
