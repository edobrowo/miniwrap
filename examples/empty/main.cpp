#include "application.hpp"

class Empty : public Component {
public:
    Empty() = default;

    void update() override {}

    void draw(const Canvas& canvas) override {}
};

int main() {
    Application app;

    try {
        app.init("Example", 640, 640);
    } catch (const std::runtime_error& e) {
        eprintln("{}", e.what());
        return 1;
    }

    std::unique_ptr<Empty> empty = std::make_unique<Empty>();
    app.add(std::move(empty));

    app.start(60.0);
}
