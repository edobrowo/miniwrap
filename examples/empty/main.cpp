#include "application.hpp"

class Empty : public Component {
public:
    Empty() = default;

    void update() override {}

    void draw(const Canvas& canvas) override {}
};

int main() {
    const char* title = "Empty";
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

    std::unique_ptr<Empty> empty = std::make_unique<Empty>();
    app.add(std::move(empty));

    app.start(fps);
}
