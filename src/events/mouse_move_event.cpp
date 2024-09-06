#include "mouse_move_event.hpp"

MouseMoveEvent::MouseMoveEvent(
    const int timestamp,
    const int x,
    const int y,
    const int rel_x,
    const int rel_y)
    : Event(Event::Kind::MouseMove, timestamp),
      m_position{Point{x, y}},
      m_relative{Point{rel_x, rel_y}} {}

MouseMoveEvent::~MouseMoveEvent() {}

Point MouseMoveEvent::pos() const noexcept {
    return m_position;
}

int MouseMoveEvent::x() const noexcept {
    return m_position.x();
}

int MouseMoveEvent::y() const noexcept {
    return m_position.y();
}

Point MouseMoveEvent::posRelative() const noexcept {
    return m_relative;
}

int MouseMoveEvent::xRelative() const noexcept {
    return m_relative.x();
}

int MouseMoveEvent::yRelative() const noexcept {
    return m_relative.y();
}
