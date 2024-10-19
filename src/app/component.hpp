#pragma once

#include "canvas.hpp"
#include "event.hpp"
#include "event_names.hpp"
#include "keyboard_event.hpp"
#include "mouse_click_event.hpp"
#include "mouse_move_event.hpp"
#include "mouse_scroll_event.hpp"
#include "quit_event.hpp"

class Component {
public:
    Component();
    virtual ~Component() = 0;

    virtual void event(const Event* event);

    virtual void onMouseClick(const MouseClickEvent* event) {}
    virtual void onMouseMove(const MouseMoveEvent* event) {}
    virtual void onMouseScroll(const MouseScrollEvent* event) {}
    virtual void onKeyPress(const KeyboardEvent* event) {}
    virtual void onQuit(const QuitEvent* event);

    virtual void update() {}
    virtual void draw(const Canvas& canvas) {}

    bool isRunning();

protected:
    void eventMultiplex(const Event* event);
    void quit();

    bool m_running;
};
