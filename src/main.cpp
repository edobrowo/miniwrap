#include <iostream>
#include <memory>

#include "application.hpp"
#include "canvas.hpp"

namespace {
struct AppSettings {
    const char* title;
    size_t width;
    size_t height;
};

constexpr AppSettings settings{"EXAMPLE", 640, 640};
}

int main() {
    Application app{settings.title, settings.width, settings.height};

    try {
        app.init();
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }

    std::unique_ptr<Canvas> canvas = std::make_unique<Canvas>();
    app.addComponent(std::move(canvas));

    app.start();
}
