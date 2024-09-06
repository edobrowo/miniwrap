#ifndef __KEYBOARD_EVENT__
#define __KEYBOARD_EVENT__

#include "event.hpp"
#include "event_names.hpp"
#include "key_modifiers.hpp"

class KeyboardEvent : public Event {
public:
    KeyboardEvent(
        const int timestamp,
        keyboard::Keycode keycode,
        uint16_t mod_flags);
    ~KeyboardEvent();

    keyboard::Keycode keycode() const noexcept;
    KeyModifiers modifiers() const noexcept;

private:
    keyboard::Keycode m_keycode;
    KeyModifiers m_modifiers;
};

#endif
