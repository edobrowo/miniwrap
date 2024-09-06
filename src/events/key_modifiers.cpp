#include "key_modifiers.hpp"

bool KeyModifiers::shift() const noexcept {
    return m_modifiers | static_cast<uint16_t>(keyboard::Modifier::Shift);
}

bool KeyModifiers::shiftL() const noexcept {
    return m_modifiers | static_cast<uint16_t>(keyboard::Modifier::ShiftL);
}

bool KeyModifiers::shiftR() const noexcept {
    return m_modifiers | static_cast<uint16_t>(keyboard::Modifier::ShiftR);
}

bool KeyModifiers::control() const noexcept {
    return m_modifiers | static_cast<uint16_t>(keyboard::Modifier::Control);
}

bool KeyModifiers::controlL() const noexcept {
    return m_modifiers | static_cast<uint16_t>(keyboard::Modifier::ControlL);
}

bool KeyModifiers::controlR() const noexcept {
    return m_modifiers | static_cast<uint16_t>(keyboard::Modifier::ControlR);
}

bool KeyModifiers::option() const noexcept {
    return m_modifiers | static_cast<uint16_t>(keyboard::Modifier::Option);
}

bool KeyModifiers::optionL() const noexcept {
    return m_modifiers | static_cast<uint16_t>(keyboard::Modifier::OptionL);
}

bool KeyModifiers::optionR() const noexcept {
    return m_modifiers | static_cast<uint16_t>(keyboard::Modifier::OptionR);
}

bool KeyModifiers::command() const noexcept {
    return m_modifiers | static_cast<uint16_t>(keyboard::Modifier::Command);
}

bool KeyModifiers::commandL() const noexcept {
    return m_modifiers | static_cast<uint16_t>(keyboard::Modifier::CommandL);
}

bool KeyModifiers::commandR() const noexcept {
    return m_modifiers | static_cast<uint16_t>(keyboard::Modifier::CommandR);
}

bool KeyModifiers::capsLock() const noexcept {
    return m_modifiers | static_cast<uint16_t>(keyboard::Modifier::CapsLock);
}
