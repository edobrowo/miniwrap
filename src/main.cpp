#include <SDL2/SDL.h>

#include <iostream>
#include <vector>

#include "color.hpp"
#include "renderer.hpp"
#include "vec2.hpp"
#include "window.hpp"

int main() {
    int err = SDL_Init(SDL_INIT_VIDEO);
    if (err != 0) {
        std::string message = std::string("Failed to update SDL window") + SDL_GetError();
        throw std::runtime_error(message);
    }

    const WindowSettings windowSettings{"FABRIK IK", 640, 640};
    Window window{windowSettings.title, windowSettings.width, windowSettings.height};

    Renderer renderer = Renderer();

    try {
        window.init();
        std::shared_ptr<Window> window_ref(&window, [](auto) {});
        renderer.init(window_ref);
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }

    std::vector<Vec2> joints;

    Color clear_color(0, 0, 0);
    Color arm_color{255, 0, 0};

    SDL_Event event;
    bool quit = false;
    while (!quit) {
        renderer.clear(clear_color);
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            } else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_q) {
                    quit = true;
                }
                if (event.key.keysym.sym == SDLK_r) {
                    joints.clear();
                }
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                int x, y;
                if (event.button.button == SDL_BUTTON_LEFT) {
                    SDL_GetMouseState(&x, &y);
                    joints.push_back(Vec2(x, y));
                }
            }
        }

        Vec2* prev = nullptr;
        for (Vec2& joint : joints) {
            renderer.rectFill({static_cast<int>(joint.x()) - 5, static_cast<int>(joint.y()) - 5, 10, 10}, arm_color);
            if (prev != nullptr) {
                renderer.line({static_cast<int>(prev->x()), static_cast<int>(prev->y()), static_cast<int>(joint.x()), static_cast<int>(joint.y())}, arm_color);
            }
            prev = &joint;
        }

        renderer.displayFrame();
    }

    SDL_Quit();
}
