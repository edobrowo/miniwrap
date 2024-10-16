#pragma once

#include "common.hpp"
#include "event.hpp"
#include "event_names.hpp"
#include "point.hpp"

class MouseClickEvent : public Event {
public:
    Point2I pos;
    MouseButton button;
    MouseButtonState state;
    u32 clickCount;

    MouseClickEvent(const u64 timestamp, const i32 x, const i32 y,
                    const MouseButton button, const bool is_pressed,
                    const u32 click_count);

    bool isPressed() const;
    bool isReleased() const;

    bool isLeftClick() const;
    bool isRightClick() const;

    i32 x() const;
    i32 y() const;

    bool isSingleClick() const;
    bool isDoubleClick() const;
};
