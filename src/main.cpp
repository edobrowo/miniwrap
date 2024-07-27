#include <iostream>

#include "fabrik.hpp"

int main() {
    try {
        Fabrik().start();
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }
}
