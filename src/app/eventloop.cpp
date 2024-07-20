#include "eventloop.hpp"

#include <SDL2/SDL.h>

#include <iostream>

#include "application.hpp"

EventLoop::EventLoop() : m_running{false} {}

void EventLoop::start(Application& app) {
    m_running = true;
    run(app);
}

void EventLoop::quit() {
    m_running = false;
}

void EventLoop::run(Application& app) {
    SDL_Event event;
    while (m_running) {
        while (SDL_PollEvent(&event)) {
            app.event(event);
        }
        app.update();
    }
}
