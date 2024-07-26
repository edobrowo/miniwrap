#include "fabrikik.hpp"

FabrikIKApp::FabrikIKApp() {
    //
}

FabrikIKApp::~FabrikIKApp() {
    //
}

void FabrikIKApp::event(const SDL_Event& event) {
    if (event.type == SDL_QUIT) {
        quit();
    } else if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_q) {
            quit();
        }
        if (event.key.keysym.sym == SDLK_r) {
            m_joints.clear();
        }
    } else if (event.type == SDL_MOUSEBUTTONDOWN) {
        int x, y;
        if (event.button.button == SDL_BUTTON_LEFT) {
            SDL_GetMouseState(&x, &y);
            m_joints.push_back(Vec2(x, y));
        }
    }
}

void FabrikIKApp::update() {
    render().clear(m_clearColor);

    Vec2* prev = nullptr;
    for (Vec2& joint : m_joints) {
        render().rectFill({static_cast<int>(joint.x()) - 5, static_cast<int>(joint.y()) - 5, 10, 10}, m_armColor);
        if (prev != nullptr) {
            render().line({static_cast<int>(prev->x()), static_cast<int>(prev->y()), static_cast<int>(joint.x()), static_cast<int>(joint.y())}, m_armColor);
        }
        prev = &joint;
    }

    render().show();
}
