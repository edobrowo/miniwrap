#pragma once

#include <map>
#include <vector>

#include "color.hpp"
#include "component.hpp"
#include "point.hpp"
#include "rect.hpp"
#include "vector.hpp"

class Canvas : public Component {
public:
    Canvas();
    ~Canvas() override;

    void onMouseClick(const MouseClickEvent* event) override;
    void onMouseMove(const MouseMoveEvent* event) override;
    void onKeyPress(const KeyboardEvent* event) override;

    void update() override;
    void render(const Renderer& renderer) override;

private:
    std::vector<Vector2D> m_joints;
    Vector2D* m_target;

    Point2I m_mousePos;
    bool m_placing;
    bool m_dragging;
};
