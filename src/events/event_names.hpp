#pragma once

enum class MouseButton {
    Left = 0,
    Right,
    Middle,
};

enum class MouseButtonState {
    Pressed = 0,
    Released,
};

enum class ScrollDirection { Up = 0, Down };

enum class KeyState {
    Pressed = 0,
    Released,
};

enum class Keycode {
    None = 0,

    A,
    B,
    C,
    D,
    E,
    F,
    G,
    H,
    I,
    J,
    K,
    L,
    M,
    N,
    O,
    P,
    Q,
    R,
    S,
    T,
    U,
    V,
    W,
    X,
    Y,
    Z,

    N1,
    N2,
    N3,
    N4,
    N5,
    N6,
    N7,
    N8,
    N9,
    N0,

    BracketL,
    BracketR,
    Colon,
    Quote,
    AngleL,
    AngleR,
    Slash,
    Backslash,
    Backquote,

    Space,
    Return,
    Backspace,
    Escape,
    Tab,
    Delete,
    CapsLock,
    Function,

    ShiftL,
    ShiftR,
    CtrlL,
    CtrlR,
    AltL,
    AltR,
    GuiL,
    GuiR,

    Up,
    Down,
    Left,
    Right,

    F1,
    F2,
    F3,
    F4,
    F5,
    F6,
    F7,
    F8,
    F9,
    F10,
    F11,
    F12,
};

enum class KeyModifier {
    None = 0x0000,
    ShiftL = 0x0001,
    ShiftR = 0x0002,
    CtrlL = 0x0040,
    CtrlR = 0x0080,
    AltL = 0x0100,
    AltR = 0x0200,
    GuiL = 0x0400,
    GuiR = 0x0800,
    CapsLock = 0x2000,

    Shift = ShiftL | ShiftR,
    Ctrl = CtrlL | CtrlR,
    Alt = AltL | AltR,
    Gui = GuiL | GuiR,

    ControlL = CtrlL,
    ControlR = CtrlR,
    Control = Ctrl,
    OptionL = AltL,
    OptionR = AltR,
    Option = Alt,
    CommandL = GuiL,
    CommandR = GuiR,
    Command = Gui,
};
