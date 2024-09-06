#ifndef __CANVAS__
#define __CANVAS__

#include <vector>

#include "color.hpp"
#include "point.hpp"
#include "vec2.hpp"
#include "widget.hpp"

class Canvas : public Widget {
public:
    Canvas();
    ~Canvas() override;

    void event(const SDL_Event& event) override;
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
