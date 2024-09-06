#include "mouse_event.hpp"

MouseClickEvent::MouseClickEvent(
    const int timestamp,
    const int x,
    const int y,
    const mouse::Button button,
    const bool is_pressed,
    const int click_count)
    : Event(Event::Kind::MouseClick, timestamp),
      m_position{Point(x, y)},
      m_button{button},
      m_state{is_pressed ? mouse::ButtonState::Pressed : mouse::ButtonState::Released},
      m_clickCount{click_count} {}

MouseClickEvent::~MouseClickEvent() {}

bool MouseClickEvent::isPressed() const noexcept {
    return m_state == mouse::ButtonState::Pressed;
}

bool MouseClickEvent::isReleased() const noexcept {
    return m_state == mouse::ButtonState::Released;
}

mouse::Button MouseClickEvent::button() const noexcept {
    return m_button;
}

Point MouseClickEvent::pos() const noexcept {
    return m_position;
}

int MouseClickEvent::x() const noexcept {
    return m_position.x();
}

int MouseClickEvent::y() const noexcept {
    return m_position.y();
}

int MouseClickEvent::clickCount() const noexcept {
    return m_clickCount;
}

bool MouseClickEvent::isSingleClick() const noexcept {
    return m_clickCount == 1;
}

bool MouseClickEvent::isDoubleClick() const noexcept {
    return m_clickCount == 2;
}
