#include <iostream>
#include <memory>

#include "application.hpp"

class Canvas : public Component {
public:
    Canvas() = default;
    ~Canvas() = default;

    void render(const Renderer& renderer) override {
        Point2I center(320, 320);
        i32 radius = 100;

        renderer.clear(Color(0.0, 0.0, 0.0));
        renderer.setColor(Color(1.0, 0.0, 0.0));
        renderer.circleFill(center, radius);
        renderer.setColor(Color(0.0, 0.0, 1.0));
        renderer.circleOutline(center, radius);
        renderer.show();
    }
};

int main() {
    Application app("Circles", 640, 640);

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
