#include "event_builder.hpp"

#include "event_names.hpp"
#include "keyboard_event.hpp"
#include "mouse_click_event.hpp"
#include "mouse_move_event.hpp"
#include "mouse_scroll_event.hpp"

namespace {
    Event fromSdlMouseMotionEvent(const SDL_MouseMotionEvent* event) {
        return MouseMoveEvent{
            event->timestamp,
            event->x,
            event->y,
            event->xrel,
            event->yrel,
        };
    }

    mouse::Button fromSdlButton(const Uint8 button) {
        switch (button) {
        case SDL_BUTTON_LEFT:
            return mouse::Button::Left;
        case SDL_BUTTON_RIGHT:
            return mouse::Button::Right;
        case SDL_BUTTON_MIDDLE:
            return mouse::Button::Middle;
        default:
            // unimplemented
            return mouse::Button::Left;
        }
    }

    Event fromSdlMouseButtonEvent(const SDL_MouseButtonEvent* event) {
        return MouseClickEvent{
            event->timestamp,
            event->x,
            event->y,
            fromSdlButton(event->button),
            event->state == SDL_PRESSED,
            event->clicks,
        };
    }

    mouse::ScrollDirection fromSdlScrollDirection(const Uint32 direction) {
        switch (direction) {
        case SDL_MOUSEWHEEL_NORMAL:
            return mouse::ScrollDirection::Up;
        case SDL_MOUSEWHEEL_FLIPPED:
            return mouse::ScrollDirection::Down;
        }
    }

    Event fromSdlMouseWheelEvent(const SDL_MouseWheelEvent* event) {
        return MouseScrollEvent{
            event->timestamp,
            event->x,
            event->y,
            fromSdlScrollDirection(event->direction),
            event->preciseX,
            event->preciseY,
        };
    }

    Event fromSdlKeyboardEvent(const SDL_KeyboardEvent* event) {
        //
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
    default:
        // unimplemented
        return Event{};
    }
}
