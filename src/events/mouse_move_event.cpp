#include "mouse_move_event.hpp"

MouseMoveEvent::MouseMoveEvent(const u64 timestamp, const i32 x, const i32 y,
                               const i32 rel_x, const i32 rel_y)
    : Event(Event::Kind::MouseMove, timestamp), pos(x, y), rel(rel_x, rel_y) {}

int MouseMoveEvent::x() const { return pos.x; }

int MouseMoveEvent::y() const { return pos.y; }

int MouseMoveEvent::xrel() const { return rel.x; }

int MouseMoveEvent::yrel() const { return rel.y; }
