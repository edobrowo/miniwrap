#include <map>
#include <vector>

#include "application.hpp"
#include "math.hpp"
#include "point.hpp"
#include "vector.hpp"

namespace colors {
const Color arm(1.0, 0.0, 0.0);
const Color arm_highlight(1.0, 1.0, 0.0);
}

namespace {
Rect2I build_joint_bounds(const Vector2D& joint) {
    Point2I p(joint.x, joint.y);
    return {p.x - 5, p.y - 5, 10, 10};
}
}

class PolylineDrawer : public Component {
public:
    PolylineDrawer();
    ~PolylineDrawer() override;

    void onMouseClick(const MouseClickEvent* event) override;
    void onMouseMove(const MouseMoveEvent* event) override;
    void onKeyPress(const KeyboardEvent* event) override;

    void draw(const Canvas& canvas) override;

private:
    std::vector<Vector2D> m_joints;
    Vector2D* m_target;

    Point2I m_mousePos;
    bool m_placing;
    bool m_dragging;
};

PolylineDrawer::PolylineDrawer()
    : Component(), m_target(nullptr), m_placing(true), m_dragging(false) {}

PolylineDrawer::~PolylineDrawer() {}

void PolylineDrawer::onMouseClick(const MouseClickEvent* event) {
    for (Vector2D& joint : m_joints) {
        Rect2I joint_bounds = build_joint_bounds(joint);
        if (joint_bounds.contains(event->pos)) {
            m_dragging = true;
            m_target = &joint;
        }
    }

    if (m_placing && !m_dragging && event->isLeftClick()) {
        m_joints.push_back(Vector2D(event->x(), event->y()));
    }

    if (event->isReleased()) {
        m_dragging = false;
    }
}

void PolylineDrawer::onMouseMove(const MouseMoveEvent* event) {
    m_mousePos = event->pos;

    if (m_dragging) {
        *m_target = Vector2D(event->x(), event->y());
    }
}

void PolylineDrawer::onKeyPress(const KeyboardEvent* event) {
    if (!event->isPressed()) {
        return;
    }

    switch (event->keycode) {
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

void PolylineDrawer::draw(const Canvas& canvas) {
    canvas.setColor(colors::arm);

    std::vector<Point2I> points;
    points.reserve(m_joints.size());
    for (const Vector2D& joint : m_joints) {
        points.emplace_back(joint);
    }
    canvas.polyline(points);

    for (const Point2I& point : points) {
        Rect2I joint_rect(point.x - 5, point.y - 5, 10, 10);

        canvas.setColor(colors::arm);
        if (joint_rect.contains(m_mousePos))
            canvas.setColor(colors::arm_highlight);

        canvas.rect(joint_rect);
    }

    if (!m_joints.empty() && m_placing) {
        const Vector2D& last = m_joints.back();
        canvas.line(Point2I(last.x, last.y), m_mousePos);
    }
}

int main() {
    Application app;

    try {
        app.init("Interactive Polyline", 640, 640);
    } catch (const std::runtime_error& e) {
        eprintln("{}", e.what());
        return 1;
    }

    std::unique_ptr<PolylineDrawer> polyline_drawer =
        std::make_unique<PolylineDrawer>();
    app.add(std::move(polyline_drawer));

    app.start(60.0);
}
