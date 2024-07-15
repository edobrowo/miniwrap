#include <SDL2/SDL.h>

#include <iostream>

#include "color.hpp"
#include "renderer.hpp"
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

    SDL_Event event;
    bool quit = false;
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            } else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_q) {
                    quit = true;
                }
            }
        }
    }

    SDL_Quit();
}
