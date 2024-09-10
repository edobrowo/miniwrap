#include "mouse_scroll_event.hpp"

MouseScrollEvent::MouseScrollEvent(
    const int timestamp,
    const int x,
    const int y,
    const ScrollDirection direction,
    const float scroll_horizontal,
    const float scroll_vertical)
    : Event{Event::Kind::MouseScroll, timestamp},
      m_position{Point{x, y}},
      m_direction{direction},
      m_horizontal{scroll_horizontal},
      m_vertical{scroll_vertical} {}

MouseScrollEvent::~MouseScrollEvent() {}

Point MouseScrollEvent::pos() const noexcept {
    return m_position;
}

int MouseScrollEvent::x() const noexcept {
    return m_position.x();
}

int MouseScrollEvent::y() const noexcept {
    return m_position.y();
}

ScrollDirection MouseScrollEvent::direction() const noexcept {
    return m_direction;
}

float MouseScrollEvent::horizontal() const noexcept {
    return m_horizontal;
}

float MouseScrollEvent::vertical() const noexcept {
    return m_vertical;
}
