#include "mouse_move_event.hpp"

MouseMoveEvent::MouseMoveEvent(const u64 timestamp, const i32 x, const i32 y,
                               const i32 rel_x, const i32 rel_y)
    : Event(Event::Kind::MouseMove, timestamp), pos(x, y), rel(rel_x, rel_y) {}

i32 MouseMoveEvent::x() const { return pos.x; }

i32 MouseMoveEvent::y() const { return pos.y; }

i32 MouseMoveEvent::xrel() const { return rel.x; }

i32 MouseMoveEvent::yrel() const { return rel.y; }
