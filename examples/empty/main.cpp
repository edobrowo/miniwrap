#include "application.hpp"

class Canvas : public Component {
public:
    Canvas() = default;

    void update(const FrameInfo& info) override {}

    void render(const Renderer& renderer) override {
        renderer.clear(Color(0.0, 0.0, 0.0));
        renderer.show();
    }
};

int main() {
    Application app("Example", 640, 640);

    try {
        app.init();
    } catch (const std::runtime_error& e) {
        eprintln("{}", e.what());
        return 1;
    }

    std::unique_ptr<Canvas> canvas = std::make_unique<Canvas>();
    app.addComponent(std::move(canvas));

    app.start(60.0);
}
