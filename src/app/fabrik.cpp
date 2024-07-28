#include "fabrik.hpp"

namespace {
    struct AppSettings {
        const char* title;
        size_t width;
        size_t height;
    };

    constexpr AppSettings settings{"FABRIK", 640, 640};
}

Fabrik::Fabrik() : Application(settings.title, settings.width, settings.height), m_placing{true} {
}

Fabrik::~Fabrik() {}

void Fabrik::event(const SDL_Event& event) {
    if (event.type == SDL_QUIT) {
        quit();
    } else if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_q) {
            quit();
        } else if (event.key.keysym.sym == SDLK_r) {
            m_joints.clear();
        } else if (event.key.keysym.sym == SDLK_e) {
            m_placing = !m_placing;
        }
    } else if (event.type == SDL_MOUSEBUTTONDOWN) {
        int x, y;
        if (event.button.button == SDL_BUTTON_LEFT && m_placing) {
            SDL_GetMouseState(&x, &y);
            m_joints.push_back(Vec2(x, y));
        }
    } else if (event.type == SDL_MOUSEMOTION) {
        int x, y;
        SDL_GetMouseState(&x, &y);
        m_mousePos.setX(x);
        m_mousePos.setY(y);
    }
}

void Fabrik::update() {
    render().clear(m_clearColor);

    render().setColor(m_armColor);
    Vec2* prev = nullptr;
    for (Vec2& joint : m_joints) {
        render().rectFill(Rect(static_cast<int>(joint.x()) - 5, static_cast<int>(joint.y()) - 5, 10, 10));
        if (prev != nullptr) {
            render().line(Line(static_cast<int>(prev->x()), static_cast<int>(prev->y()), static_cast<int>(joint.x()), static_cast<int>(joint.y())));
        }
        prev = &joint;
    }

    if (!m_joints.empty() && m_placing) {
        const Vec2& last = m_joints.back();
        render().line(Line(Point(last.x(), last.y()), m_mousePos));
    }

    render().show();
}

// TODO
// - current base should be highlighted
// - hovering over joints highlights them
// - clicking a joint sets it as the new base in select mode
