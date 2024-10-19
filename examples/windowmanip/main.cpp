#include "application.hpp"

class WindowManipulator : public Component {
public:
    WindowManipulator(Application* app) : m_app(app) {
        m_pos = m_app->window().pos();
    }

    void onKeyPress(const KeyboardEvent* event) override {
        if (!event->isPressed()) {
            return;
        }

        switch (event->keycode) {
        case Keycode::W:
            m_pos.y -= 5;
            break;
        case Keycode::A:
            m_pos.x -= 5;
            break;
        case Keycode::S:
            m_pos.y += 5;
            break;
        case Keycode::D:
            m_pos.x += 5;
            break;
        default:
            break;
        }
    }

    void update() override { m_app->windowMut().setPos(m_pos.x, m_pos.y); }

private:
    Application* m_app;
    Point2I m_pos;
};

int main() {
    Application app;

    try {
        app.init("Window Manipulation", 640, 640);
    } catch (const std::runtime_error& e) {
        eprintln("{}", e.what());
        return 1;
    }

    std::unique_ptr<WindowManipulator> window_manipulator =
        std::make_unique<WindowManipulator>(&app);
    app.add(std::move(window_manipulator));

    app.start(60.0);
}
