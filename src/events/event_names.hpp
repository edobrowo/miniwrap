#ifndef __EVENT_NAMES__
#define __EVENT_NAMES__

namespace mouse {
    enum class Button {
        Left = 0,
        Right,
        Middle,
    };

    enum class ButtonState {
        Pressed = 0,
        Released,
    };

    enum class ScrollDirection {
        Up = 0,
        Down
    };
}

namespace keyboard {
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
        Tilde,

        Space,
        Return,
        Backspace,
        Escape,
        Tab,
        Control,
        Delete,
        CapsLock,
        Function,

        ShiftL,
        ShiftR,
        OptionL,
        OptionR,
        CommandL,
        CommandR,

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

    enum class Modifier {
        None = 0x0000,
        ShiftL = 0x0001,
        ShiftR = 0x0002,
        ControlL = 0x0040,
        ControlR = 0x0080,
        OptionL = 0x0100,
        OptionR = 0x0200,
        CommandL = 0x0400,
        CommandR = 0x0800,
        CapsLock = 0x2000,

        Shift = ShiftL | ShiftR,
        Control = ControlL | ControlR,
        Option = OptionL | OptionR,
        Command = CommandL | CommandR,
    };
}

#endif
