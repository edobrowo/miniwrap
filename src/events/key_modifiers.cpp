#include "key_modifiers.hpp"

KeyModifiers::KeyModifiers(const u16 mod_flags) : m_modifiers(mod_flags) {}

KeyModifiers::~KeyModifiers() {}

bool KeyModifiers::shift() const {
    return m_modifiers | static_cast<u16>(KeyModifier::Shift);
}

bool KeyModifiers::shiftL() const {
    return m_modifiers | static_cast<u16>(KeyModifier::ShiftL);
}

bool KeyModifiers::shiftR() const {
    return m_modifiers | static_cast<u16>(KeyModifier::ShiftR);
}

bool KeyModifiers::ctrl() const {
    return m_modifiers | static_cast<u16>(KeyModifier::Ctrl);
}

bool KeyModifiers::ctrlL() const {
    return m_modifiers | static_cast<u16>(KeyModifier::CtrlL);
}

bool KeyModifiers::ctrlR() const {
    return m_modifiers | static_cast<u16>(KeyModifier::CtrlR);
}

bool KeyModifiers::control() const {
    return m_modifiers | static_cast<u16>(KeyModifier::Ctrl);
}

bool KeyModifiers::controlL() const {
    return m_modifiers | static_cast<u16>(KeyModifier::CtrlL);
}

bool KeyModifiers::controlR() const {
    return m_modifiers | static_cast<u16>(KeyModifier::CtrlR);
}

bool KeyModifiers::alt() const {
    return m_modifiers | static_cast<u16>(KeyModifier::Alt);
}

bool KeyModifiers::altL() const {
    return m_modifiers | static_cast<u16>(KeyModifier::AltL);
}

bool KeyModifiers::altR() const {
    return m_modifiers | static_cast<u16>(KeyModifier::AltR);
}

bool KeyModifiers::option() const {
    return m_modifiers | static_cast<u16>(KeyModifier::Alt);
}

bool KeyModifiers::optionL() const {
    return m_modifiers | static_cast<u16>(KeyModifier::AltL);
}

bool KeyModifiers::optionR() const {
    return m_modifiers | static_cast<u16>(KeyModifier::AltR);
}

bool KeyModifiers::gui() const {
    return m_modifiers | static_cast<u16>(KeyModifier::Gui);
}

bool KeyModifiers::guiL() const {
    return m_modifiers | static_cast<u16>(KeyModifier::GuiL);
}

bool KeyModifiers::guiR() const {
    return m_modifiers | static_cast<u16>(KeyModifier::GuiR);
}

bool KeyModifiers::command() const {
    return m_modifiers | static_cast<u16>(KeyModifier::Gui);
}

bool KeyModifiers::commandL() const {
    return m_modifiers | static_cast<u16>(KeyModifier::GuiL);
}

bool KeyModifiers::commandR() const {
    return m_modifiers | static_cast<u16>(KeyModifier::GuiR);
}

bool KeyModifiers::capsLock() const {
    return m_modifiers | static_cast<u16>(KeyModifier::CapsLock);
}
