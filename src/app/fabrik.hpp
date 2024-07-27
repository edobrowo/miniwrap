#ifndef __FABRIKIK__
#define __FABRIKIK__

#include <vector>

#include "application.hpp"
#include "vec2.hpp"

class Fabrik : public Application {
public:
    Fabrik();
    ~Fabrik();

    void event(const SDL_Event& event) override;
    void update() override;

private:
    std::vector<Vec2> m_joints;
    const Color m_clearColor{0, 0, 0};
    const Color m_armColor{255, 0, 0};
};

#endif
