#pragma once

#include <stdlib.h>

#include "common.hpp"
#include "event_names.hpp"

class KeyModifiers {
public:
    KeyModifiers(const u16 mod_flags);
    ~KeyModifiers();

    bool shift() const;
    bool shiftL() const;
    bool shiftR() const;

    bool ctrl() const;
    bool ctrlL() const;
    bool ctrlR() const;
    bool control() const;
    bool controlL() const;
    bool controlR() const;

    bool alt() const;
    bool altL() const;
    bool altR() const;
    bool option() const;
    bool optionL() const;
    bool optionR() const;

    bool gui() const;
    bool guiL() const;
    bool guiR() const;
    bool command() const;
    bool commandL() const;
    bool commandR() const;

    bool capsLock() const;

private:
    u16 m_modifiers;
};
