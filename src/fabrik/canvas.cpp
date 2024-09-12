#include "canvas.hpp"

#include <cmath>
#include <iostream>

#include "event_names.hpp"
#include "keyboard_event.hpp"
#include "mouse_click_event.hpp"
#include "mouse_move_event.hpp"

Canvas::Canvas() : Component(), m_placing{true} {}

Canvas::~Canvas() {}

void Canvas::onMouseClick(const MouseClickEvent* event) {
    if (m_placing && event->isPressed() &&
        event->button() == MouseButton::Left) {
        m_joints.push_back(Vec2(event->x(), event->y()));
    }
}

void Canvas::onMouseMove(const MouseMoveEvent* event) {
    m_mousePos = event->pos();
}

void Canvas::onKeyPress(const KeyboardEvent* event) {
    if (!event->isPressed()) {
        return;
    }

    switch (event->keycode()) {
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
}

void Canvas::update() {}

void Canvas::render(const Renderer& renderer) {
    renderer.clear(m_clearColor);

    renderer.setColor(m_armColor);
    Vec2* prev = nullptr;
    for (Vec2& joint : m_joints) {
        renderer.rectFill(
            Rect(std::floor(joint.x()) - 5, std::floor(joint.y()) - 5, 10, 10));
        if (prev != nullptr) {
            renderer.line(Line(std::floor(prev->x()), std::floor(prev->y()),
                               std::floor(joint.x()), std::floor(joint.y())));
        }
        prev = &joint;
    }

    if (!m_joints.empty() && m_placing) {
        const Vec2& last = m_joints.back();
        renderer.line(Line(Point(last.x(), last.y()), m_mousePos));
    }

    renderer.show();
}
