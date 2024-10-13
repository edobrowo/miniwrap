#pragma once

#include "common.hpp"
#include "event.hpp"
#include "event_names.hpp"
#include "key_modifiers.hpp"

class KeyboardEvent : public Event {
public:
    Keycode keycode;
    KeyState state;
    KeyModifiers modifiers;

    KeyboardEvent(const u64 timestamp, const Keycode keycode,
                  const bool is_pressed, const u16 mod_flags);

    bool isPressed() const;
    bool isReleased() const;
};
