#include "event_builder.hpp"

#include <map>

#include "event_names.hpp"
#include "keyboard_event.hpp"
#include "mouse_click_event.hpp"
#include "mouse_move_event.hpp"
#include "mouse_scroll_event.hpp"
#include "quit_event.hpp"

namespace {

MouseMoveEvent fromSdlMouseMotionEvent(const SDL_MouseMotionEvent* event) {
    return MouseMoveEvent{
        static_cast<int>(event->timestamp),
        event->x,
        event->y,
        event->xrel,
        event->yrel,
    };
}

MouseButton fromSdlButton(const Uint8 button) {
    switch (button) {
    case SDL_BUTTON_LEFT:
        return MouseButton::Left;
    case SDL_BUTTON_RIGHT:
        return MouseButton::Right;
    case SDL_BUTTON_MIDDLE:
        return MouseButton::Middle;
    default:
        // unimplemented
        return MouseButton::Left;
    }
}

MouseClickEvent fromSdlMouseButtonEvent(const SDL_MouseButtonEvent* event) {
    return MouseClickEvent{
        static_cast<int>(event->timestamp),
        event->x,
        event->y,
        fromSdlButton(event->button),
        event->state == SDL_PRESSED,
        event->clicks,
    };
}

ScrollDirection fromSdlScrollDirection(const Uint32 direction) {
    switch (direction) {
    case SDL_MOUSEWHEEL_NORMAL:
        return ScrollDirection::Up;
    case SDL_MOUSEWHEEL_FLIPPED:
        return ScrollDirection::Down;
    default:
        return ScrollDirection::Up;
    }
}

MouseScrollEvent fromSdlMouseWheelEvent(const SDL_MouseWheelEvent* event) {
    return MouseScrollEvent{
        static_cast<int>(event->timestamp),
        event->x,
        event->y,
        fromSdlScrollDirection(event->direction),
        event->preciseX,
        event->preciseY,
    };
}

const std::map<SDL_KeyCode, Keycode> keymap{
    {SDLK_UNKNOWN, Keycode::None},

    {SDLK_a, Keycode::A},
    {SDLK_b, Keycode::B},
    {SDLK_c, Keycode::C},
    {SDLK_d, Keycode::D},
    {SDLK_e, Keycode::E},
    {SDLK_f, Keycode::F},
    {SDLK_g, Keycode::G},
    {SDLK_h, Keycode::H},
    {SDLK_i, Keycode::I},
    {SDLK_j, Keycode::J},
    {SDLK_k, Keycode::K},
    {SDLK_l, Keycode::L},
    {SDLK_m, Keycode::M},
    {SDLK_n, Keycode::N},
    {SDLK_o, Keycode::O},
    {SDLK_p, Keycode::P},
    {SDLK_q, Keycode::Q},
    {SDLK_r, Keycode::R},
    {SDLK_s, Keycode::S},
    {SDLK_t, Keycode::T},
    {SDLK_u, Keycode::U},
    {SDLK_v, Keycode::V},
    {SDLK_w, Keycode::W},
    {SDLK_x, Keycode::X},
    {SDLK_y, Keycode::Y},
    {SDLK_z, Keycode::Z},

    {SDLK_0, Keycode::N0},
    {SDLK_1, Keycode::N1},
    {SDLK_2, Keycode::N2},
    {SDLK_3, Keycode::N3},
    {SDLK_4, Keycode::N4},
    {SDLK_5, Keycode::N5},
    {SDLK_6, Keycode::N6},
    {SDLK_7, Keycode::N7},
    {SDLK_8, Keycode::N8},
    {SDLK_9, Keycode::N9},

    {SDLK_LEFTBRACKET, Keycode::BracketL},
    {SDLK_RIGHTBRACKET, Keycode::BracketR},
    {SDLK_COLON, Keycode::Colon},
    {SDLK_LESS, Keycode::AngleL},
    {SDLK_RIGHT, Keycode::AngleR},
    {SDLK_SLASH, Keycode::Slash},
    {SDLK_BACKSLASH, Keycode::Backslash},
    {SDLK_BACKQUOTE, Keycode::Backquote},

    {SDLK_SPACE, Keycode::Space},
    {SDLK_RETURN, Keycode::Return},
    {SDLK_BACKSPACE, Keycode::Backspace},
    {SDLK_ESCAPE, Keycode::Escape},
    {SDLK_TAB, Keycode::Tab},
    {SDLK_DELETE, Keycode::Delete},
    {SDLK_CAPSLOCK, Keycode::CapsLock},

    {SDLK_LSHIFT, Keycode::ShiftL},
    {SDLK_RSHIFT, Keycode::ShiftR},
    {SDLK_LCTRL, Keycode::CtrlL},
    {SDLK_RCTRL, Keycode::CtrlR},
    {SDLK_LALT, Keycode::AltL},
    {SDLK_RALT, Keycode::AltR},
    {SDLK_LGUI, Keycode::GuiL},
    {SDLK_RGUI, Keycode::GuiR},

    {SDLK_F1, Keycode::F1},
    {SDLK_F2, Keycode::F2},
    {SDLK_F3, Keycode::F3},
    {SDLK_F4, Keycode::F4},
    {SDLK_F5, Keycode::F5},
    {SDLK_F6, Keycode::F6},
    {SDLK_F7, Keycode::F7},
    {SDLK_F8, Keycode::F8},
    {SDLK_F9, Keycode::F9},
    {SDLK_F10, Keycode::F10},
    {SDLK_F11, Keycode::F11},
    {SDLK_F12, Keycode::F12},
};

KeyboardEvent fromSdlKeyboardEvent(const SDL_KeyboardEvent* event) {
    SDL_KeyCode sdl_keycode = static_cast<SDL_KeyCode>(event->keysym.sym);
    Keycode keycode = Keycode::None;
    if (keymap.find(sdl_keycode) != keymap.end()) {
        keycode = keymap.at(sdl_keycode);
    }
    return KeyboardEvent{
        static_cast<int>(event->timestamp),
        keycode,
        event->state == SDL_PRESSED,
        static_cast<uint16_t>(event->keysym.mod),
    };
}

QuitEvent fromSdlQuitEvent(const SDL_QuitEvent* event) {
    return QuitEvent{
        static_cast<int>(event->timestamp),
    };
}

}

Event fromSdlEvent(const SDL_Event* event) {
    switch (event->type) {
    case SDL_MOUSEMOTION:
        return fromSdlMouseMotionEvent(&event->motion);
    case SDL_MOUSEBUTTONDOWN:
    case SDL_MOUSEBUTTONUP:
        return fromSdlMouseButtonEvent(&event->button);
    case SDL_MOUSEWHEEL:
        return fromSdlMouseWheelEvent(&event->wheel);
    case SDL_KEYDOWN:
    case SDL_KEYUP:
        return fromSdlKeyboardEvent(&event->key);
    case SDL_QUIT:
        return fromSdlQuitEvent(&event->quit);
    default:
        // unimplemented
        return Event{};
    }
}
