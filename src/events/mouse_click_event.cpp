#include "mouse_click_event.hpp"

MouseClickEvent::MouseClickEvent(const u64 timestamp, const i32 x, const i32 y,
                                 const MouseButton button,
                                 const bool is_pressed, const u32 click_count)
    : Event{Event::Kind::MouseClick, timestamp},
      pos(x, y),
      button(button),
      state(is_pressed ? MouseButtonState::Pressed
                       : MouseButtonState::Released),
      clickCount(click_count) {}

bool MouseClickEvent::isPressed() const {
    return state == MouseButtonState::Pressed;
}

bool MouseClickEvent::isReleased() const {
    return state == MouseButtonState::Released;
}

bool MouseClickEvent::isLeftClick() const {
    return isPressed() && button == MouseButton::Left;
}

bool MouseClickEvent::isRightClick() const {
    return isPressed() && button == MouseButton::Right;
}

i32 MouseClickEvent::x() const { return pos.x; }

i32 MouseClickEvent::y() const { return pos.y; }

bool MouseClickEvent::isSingleClick() const { return clickCount == 1; }

bool MouseClickEvent::isDoubleClick() const { return clickCount == 2; }
