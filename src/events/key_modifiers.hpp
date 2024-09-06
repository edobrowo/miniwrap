#ifndef __KEY_MODIFIERS__
#define __KEY_MODIFIERS__

#include <stdlib.h>

#include "event_names.hpp"

class KeyModifiers {
public:
    KeyModifiers(const uint16_t mod_flags);
    ~KeyModifiers();

    bool shift() const noexcept;
    bool shiftL() const noexcept;
    bool shiftR() const noexcept;

    bool control() const noexcept;
    bool controlL() const noexcept;
    bool controlR() const noexcept;

    bool option() const noexcept;
    bool optionL() const noexcept;
    bool optionR() const noexcept;

    bool command() const noexcept;
    bool commandL() const noexcept;
    bool commandR() const noexcept;

    bool capsLock() const noexcept;

private:
    uint16_t m_modifiers;
};

#endif
