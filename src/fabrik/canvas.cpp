#include "canvas.hpp"

#include <cmath>
#include <iostream>

#include "event_names.hpp"
#include "keyboard_event.hpp"
#include "mouse_click_event.hpp"
#include "mouse_move_event.hpp"

namespace colors {

const Color clear{0, 0, 0};
const Color arm{255, 0, 0};
const Color arm_highlight{255, 255, 0};

}

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
    renderer.clear(colors::clear);

    renderer.setColor(colors::arm);

    std::vector<Point> points;
    points.reserve(m_joints.size());
    for (const Vec2& joint : m_joints) {
        points.push_back(Point{static_cast<int>(std::floor(joint.x())),
                               static_cast<int>(std::floor(joint.y()))});
    }
    renderer.polyline(points);

    for (const Point& point : points) {
        Rect joint_rect = Rect(point.x() - 5, point.y() - 5, 10, 10);

        renderer.setColor(colors::arm);
        if (joint_rect.contains(m_mousePos))
            renderer.setColor(colors::arm_highlight);

        renderer.rectFill(joint_rect);
    }

    if (!m_joints.empty() && m_placing) {
        const Vec2& last = m_joints.back();
        renderer.line(Line(Point(last.x(), last.y()), m_mousePos));
    }

    renderer.show();
}
