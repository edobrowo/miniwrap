#pragma once

#include "common.hpp"
#include "event.hpp"
#include "event_names.hpp"
#include "point.hpp"

class MouseScrollEvent : public Event {
public:
    Point2I pos;
    ScrollDirection direction;
    float horizontal;
    float vertical;

    MouseScrollEvent(const u64 timestamp, const i32 x, const i32 y,
                     const ScrollDirection direction,
                     const f64 scroll_horizontal, const f64 scroll_vertical);

    i32 x() const;
    i32 y() const;
};
