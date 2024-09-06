#include "keyboard_event.hpp"

KeyboardEvent::KeyboardEvent(
    const int timestamp,
    keyboard::Keycode keycode,
    uint16_t mod_flags)
    : Event(Event::Kind::Keyboard, timestamp),
      m_keycode{keycode},
      m_modifiers{KeyModifiers{mod_flags}} {}

KeyboardEvent::~KeyboardEvent() {}

keyboard::Keycode KeyboardEvent::keycode() const noexcept {
    return m_keycode;
}

KeyModifiers KeyboardEvent::modifiers() const noexcept {
    return m_modifiers;
}
