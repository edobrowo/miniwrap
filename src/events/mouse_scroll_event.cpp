#include "mouse_scroll_event.hpp"

MouseScrollEvent::MouseScrollEvent(const u64 timestamp, const i32 x,
                                   const i32 y, const ScrollDirection direction,
                                   const f64 scroll_horizontal,
                                   const f64 scroll_vertical)
    : Event(Event::Kind::MouseScroll, timestamp),
      pos(x, y),
      direction(direction),
      horizontal(scroll_horizontal),
      vertical(scroll_vertical) {}

i32 MouseScrollEvent::x() const { return pos.x; }

i32 MouseScrollEvent::y() const { return pos.y; }
