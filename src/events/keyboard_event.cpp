#include "keyboard_event.hpp"

KeyboardEvent::KeyboardEvent(
    const int timestamp,
    const Keycode keycode,
    const bool is_pressed,
    const uint16_t mod_flags)
    : Event{Event::Kind::Keyboard, timestamp},
      m_keycode{keycode},
      m_state{is_pressed ? KeyState::Pressed : KeyState::Released},
      m_modifiers{KeyModifiers{mod_flags}} {}

KeyboardEvent::~KeyboardEvent() {}

Keycode KeyboardEvent::keycode() const noexcept {
    return m_keycode;
}

bool KeyboardEvent::isPressed() const noexcept {
    return m_state == KeyState::Pressed;
}

bool KeyboardEvent::isReleased() const noexcept {
    return m_state == KeyState::Released;
}

KeyModifiers KeyboardEvent::modifiers() const noexcept {
    return m_modifiers;
}
