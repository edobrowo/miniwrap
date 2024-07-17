#include "application.hpp"

Application::Application() : m_mainWindow{"FABRIK IK", 640, 640}, m_loop{}, m_renderer{} {
    m_mainWindow.init();
    std::shared_ptr<Window> window_ref(&m_mainWindow, [](auto) {});
    m_renderer.init(window_ref);
}

void Application::start() {
    m_loop.start(*this);
}

void Application::event(const SDL_Event& event) {
    if (event.type == SDL_QUIT) {
        m_loop.quit();
    } else if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_q) {
            m_loop.quit();
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

void Application::update() {
    m_renderer.clear(m_clearColor);

    Vec2* prev = nullptr;
    for (Vec2& joint : m_joints) {
        m_renderer.rectFill({static_cast<int>(joint.x()) - 5, static_cast<int>(joint.y()) - 5, 10, 10}, m_armColor);
        if (prev != nullptr) {
            m_renderer.line({static_cast<int>(prev->x()), static_cast<int>(prev->y()), static_cast<int>(joint.x()), static_cast<int>(joint.y())}, m_armColor);
        }
        prev = &joint;
    }

    m_renderer.displayFrame();
}
