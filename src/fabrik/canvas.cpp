#include "canvas.hpp"

#include <iostream>

#include "event_names.hpp"
#include "keyboard_event.hpp"
#include "mouse_click_event.hpp"
#include "mouse_move_event.hpp"

Canvas::Canvas() : Component(), m_placing{true} {}

Canvas::~Canvas() {}

void Canvas::event(const Event& event) {
    if (event.kind() == Event::Kind::Quit) {
        quit();
    } else if (event.kind() == Event::Kind::Keyboard) {
        const KeyboardEvent& keyboard_event = dynamic_cast<const KeyboardEvent&>(event);

        if (!keyboard_event.isPressed()) {
            return;
        }

        switch (keyboard_event.keycode()) {
        case Keycode::Q:
            quit();
            break;
        case Keycode::R:
            m_joints.clear();
            break;
        case Keycode::E:
            m_placing = !m_placing;
            break;
        default:
            break;
        }

    } else if (event.kind() == Event::Kind::MouseClick) {
        const MouseClickEvent& click_event = dynamic_cast<const MouseClickEvent&>(event);

        if (click_event.isPressed() && click_event.button() == MouseButton::Left) {
            m_joints.push_back(Vec2(click_event.x(), click_event.y()));
        }

    } else if (event.kind() == Event::Kind::MouseMove) {
        const MouseMoveEvent& move_event = dynamic_cast<const MouseMoveEvent&>(event);
        m_mousePos = move_event.pos();
    }
}

void Canvas::update() {
}

void Canvas::render(const Renderer& renderer) {
    renderer.clear(m_clearColor);

    renderer.setColor(m_armColor);
    Vec2* prev = nullptr;
    for (Vec2& joint : m_joints) {
        renderer.rectFill(Rect(static_cast<int>(joint.x()) - 5, static_cast<int>(joint.y()) - 5, 10, 10));
        if (prev != nullptr) {
            renderer.line(Line(static_cast<int>(prev->x()), static_cast<int>(prev->y()), static_cast<int>(joint.x()), static_cast<int>(joint.y())));
        }
        prev = &joint;
    }

    if (!m_joints.empty() && m_placing) {
        const Vec2& last = m_joints.back();
        renderer.line(Line(Point(last.x(), last.y()), m_mousePos));
    }

    renderer.show();
}

// TODO
// - current base should be highlighted
// - hovering over joints highlights them
// - clicking a joint sets it as the new base in select mode
