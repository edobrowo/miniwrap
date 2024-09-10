#include "key_modifiers.hpp"

KeyModifiers::KeyModifiers(const uint16_t mod_flags) : m_modifiers{mod_flags} {}

KeyModifiers::~KeyModifiers() {}

bool KeyModifiers::shift() const noexcept {
    return m_modifiers | static_cast<uint16_t>(KeyModifier::Shift);
}

bool KeyModifiers::shiftL() const noexcept {
    return m_modifiers | static_cast<uint16_t>(KeyModifier::ShiftL);
}

bool KeyModifiers::shiftR() const noexcept {
    return m_modifiers | static_cast<uint16_t>(KeyModifier::ShiftR);
}

bool KeyModifiers::ctrl() const noexcept {
    return m_modifiers | static_cast<uint16_t>(KeyModifier::Ctrl);
}

bool KeyModifiers::ctrlL() const noexcept {
    return m_modifiers | static_cast<uint16_t>(KeyModifier::CtrlL);
}

bool KeyModifiers::ctrlR() const noexcept {
    return m_modifiers | static_cast<uint16_t>(KeyModifier::CtrlR);
}

bool KeyModifiers::control() const noexcept {
    return m_modifiers | static_cast<uint16_t>(KeyModifier::Ctrl);
}

bool KeyModifiers::controlL() const noexcept {
    return m_modifiers | static_cast<uint16_t>(KeyModifier::CtrlL);
}

bool KeyModifiers::controlR() const noexcept {
    return m_modifiers | static_cast<uint16_t>(KeyModifier::CtrlR);
}

bool KeyModifiers::alt() const noexcept {
    return m_modifiers | static_cast<uint16_t>(KeyModifier::Alt);
}

bool KeyModifiers::altL() const noexcept {
    return m_modifiers | static_cast<uint16_t>(KeyModifier::AltL);
}

bool KeyModifiers::altR() const noexcept {
    return m_modifiers | static_cast<uint16_t>(KeyModifier::AltR);
}

bool KeyModifiers::option() const noexcept {
    return m_modifiers | static_cast<uint16_t>(KeyModifier::Alt);
}

bool KeyModifiers::optionL() const noexcept {
    return m_modifiers | static_cast<uint16_t>(KeyModifier::AltL);
}

bool KeyModifiers::optionR() const noexcept {
    return m_modifiers | static_cast<uint16_t>(KeyModifier::AltR);
}

bool KeyModifiers::gui() const noexcept {
    return m_modifiers | static_cast<uint16_t>(KeyModifier::Gui);
}

bool KeyModifiers::guiL() const noexcept {
    return m_modifiers | static_cast<uint16_t>(KeyModifier::GuiL);
}

bool KeyModifiers::guiR() const noexcept {
    return m_modifiers | static_cast<uint16_t>(KeyModifier::GuiR);
}

bool KeyModifiers::command() const noexcept {
    return m_modifiers | static_cast<uint16_t>(KeyModifier::Gui);
}

bool KeyModifiers::commandL() const noexcept {
    return m_modifiers | static_cast<uint16_t>(KeyModifier::GuiL);
}

bool KeyModifiers::commandR() const noexcept {
    return m_modifiers | static_cast<uint16_t>(KeyModifier::GuiR);
}

bool KeyModifiers::capsLock() const noexcept {
    return m_modifiers | static_cast<uint16_t>(KeyModifier::CapsLock);
}
