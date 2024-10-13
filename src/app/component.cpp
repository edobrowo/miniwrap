#include "component.hpp"

Component::Component() : m_running(true) {}

Component::~Component() {}

void Component::event(const Event* event) { eventMultiplex(event); }

void Component::onMouseClick(const MouseClickEvent* event) {}

void Component::onMouseMove(const MouseMoveEvent* event) {}

void Component::onMouseScroll(const MouseScrollEvent* event) {}

void Component::onKeyPress(const KeyboardEvent* event) {}

void Component::onQuit(const QuitEvent* event) { quit(); }

void Component::update() {}

void Component::render(const Renderer& renderer) {}

bool Component::isRunning() { return m_running; }

void Component::eventMultiplex(const Event* event) {
    switch (event->kind) {
    case Event::Kind::MouseClick: {
        const MouseClickEvent* click_event =
            static_cast<const MouseClickEvent*>(event);
        onMouseClick(click_event);
        break;
    }
    case Event::Kind::MouseMove: {
        const MouseMoveEvent* move_event =
            static_cast<const MouseMoveEvent*>(event);
        onMouseMove(move_event);
        break;
    }
    case Event::Kind::MouseScroll: {
        const MouseScrollEvent* scroll_event =
            static_cast<const MouseScrollEvent*>(event);
        onMouseScroll(scroll_event);
    }
    case Event::Kind::Keyboard: {
        const KeyboardEvent* keyboard_event =
            static_cast<const KeyboardEvent*>(event);
        onKeyPress(keyboard_event);
        break;
    }
    case Event::Kind::Quit: {
        const QuitEvent* quit_event = static_cast<const QuitEvent*>(event);
        onQuit(quit_event);
        break;
    }
    default:
        break;
    }
}

void Component::quit() { m_running = false; }
