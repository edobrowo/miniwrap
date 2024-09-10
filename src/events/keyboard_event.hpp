#ifndef __KEYBOARD_EVENT__
#define __KEYBOARD_EVENT__

#include "event.hpp"
#include "event_names.hpp"
#include "key_modifiers.hpp"

class KeyboardEvent : public Event {
public:
    KeyboardEvent(
        const int timestamp,
        const Keycode keycode,
        const bool is_pressed,
        const uint16_t mod_flags);
    ~KeyboardEvent();

    Keycode keycode() const noexcept;

    bool isPressed() const noexcept;
    bool isReleased() const noexcept;

    KeyModifiers modifiers() const noexcept;

private:
    Keycode m_keycode;
    KeyState m_state;
    KeyModifiers m_modifiers;
};

#endif
