#include "eventloop.hpp"

#include <SDL2/SDL.h>

#include <iostream>

#include "application.hpp"
#include "event_builder.hpp"

EventLoop::EventLoop() : m_running{false} {}

void EventLoop::start(Application& app) {
    m_running = true;
    run(app);
}

void EventLoop::quit() { m_running = false; }

void EventLoop::run(Application& app) {
    SDL_Event sdl_event;
    while (m_running) {
        while (SDL_PollEvent(&sdl_event)) {
            Event* event = fromSdlEvent(&sdl_event);
            app.event(event);
            delete event;
        }
        app.tick();
    }
}
