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

    void event(const Event& event) override;
    void update() override;
    void render(const Renderer& renderer) override;

private:
    std::vector<Vec2> m_joints;
    Point m_mousePos;
    bool m_placing;

    const Color m_clearColor{0, 0, 0};
    const Color m_armColor{255, 0, 0};
};

#endif
