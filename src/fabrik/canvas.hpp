#ifndef __CANVAS__
#define __CANVAS__

#include <vector>

#include "color.hpp"
#include "component.hpp"
#include "point.hpp"
#include "vec2.hpp"

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
    std::vector<Vec2> m_joints;
    Point m_mousePos;
    bool m_placing;
};

#endif
