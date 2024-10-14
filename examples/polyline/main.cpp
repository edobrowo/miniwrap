#include <iostream>
#include <memory>

#include "application.hpp"
#include "canvas.hpp"
#include "format.hpp"

int main() {
    Application app("Interactive Polyline", 640, 640);

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
