#include "application.hpp"

class WindowManipulator : public Component {
public:
    WindowManipulator(Application* app) : m_app(app), m_frame(0) {
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

    void update() override {
        m_app->windowMut().setPos(m_pos.x, m_pos.y);
        StringBuffer sb;
        format(sb, "Window Manipulation - Frame {}", m_frame);
        m_app->windowMut().setTitle(sb.toString());
        ++m_frame;
    }

private:
    Application* m_app;
    Point2I m_pos;
    u64 m_frame;
};

int main() {
    const char* title = "Window Manipulation";
    constexpr u64 width = 640;
    constexpr u64 height = 640;
    constexpr u64 fps = 60;

    Application app;

    try {
        app.init(title, width, height);
    } catch (const std::runtime_error& e) {
        eprintln("{}", e.what());
        return 1;
    }

    std::unique_ptr<WindowManipulator> window_manipulator =
        std::make_unique<WindowManipulator>(&app);
    app.add(std::move(window_manipulator));

    app.start(fps);
}
