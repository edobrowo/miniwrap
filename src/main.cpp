#include <iostream>

#include "fabrikik.hpp"

int main() {
    try {
        FabrikIKApp().start();
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }
}
