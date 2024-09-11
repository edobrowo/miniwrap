#include "mouse_click_event.hpp"

MouseClickEvent::MouseClickEvent(const int timestamp, const int x, const int y,
                                 const MouseButton button,
                                 const bool is_pressed, const int click_count)
    : Event{Event::Kind::MouseClick, timestamp},
      m_position{Point(x, y)},
      m_button{button},
      m_state{is_pressed ? MouseButtonState::Pressed
                         : MouseButtonState::Released},
      m_clickCount{click_count} {}

MouseClickEvent::~MouseClickEvent() {}

bool MouseClickEvent::isPressed() const noexcept {
    return m_state == MouseButtonState::Pressed;
}

bool MouseClickEvent::isReleased() const noexcept {
    return m_state == MouseButtonState::Released;
}

MouseButton MouseClickEvent::button() const noexcept { return m_button; }

Point MouseClickEvent::pos() const noexcept { return m_position; }

int MouseClickEvent::x() const noexcept { return m_position.x(); }

int MouseClickEvent::y() const noexcept { return m_position.y(); }

int MouseClickEvent::clickCount() const noexcept { return m_clickCount; }

bool MouseClickEvent::isSingleClick() const noexcept {
    return m_clickCount == 1;
}

bool MouseClickEvent::isDoubleClick() const noexcept {
    return m_clickCount == 2;
}
