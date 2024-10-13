#include "keyboard_event.hpp"

KeyboardEvent::KeyboardEvent(const u64 timestamp, const Keycode keycode,
                             const bool is_pressed, const u16 mod_flags)
    : Event(Event::Kind::Keyboard, timestamp),
      keycode(keycode),
      state(is_pressed ? KeyState::Pressed : KeyState::Released),
      modifiers(KeyModifiers(mod_flags)) {}

bool KeyboardEvent::isPressed() const { return state == KeyState::Pressed; }

bool KeyboardEvent::isReleased() const { return state == KeyState::Released; }
