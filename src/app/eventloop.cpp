#include "eventloop.hpp"

#include <SDL2/SDL.h>

#include <iostream>

#include "application.hpp"
#include "event_builder.hpp"
#include "frameinfo.hpp"

EventLoop::EventLoop() : m_running(false) {}

void EventLoop::start(Application& app, const u64 fps) {
    m_running = true;
    run(app, fps);
}

void EventLoop::quit() { m_running = false; }

void EventLoop::run(Application& app, const u64 fps) {
    const u64 mspf = 1000 / fps;
    SDL_Event sdl_event;

    FrameInfo info{0, 0, fps};
    Timer fps_timer;
    fps_timer.start();
    while (m_running) {
        while (SDL_PollEvent(&sdl_event)) {
            Event* event = fromSdlEvent(&sdl_event);
            app.event(event);
            delete event;
        }

        if (fps_timer.elapsed() >= mspf) {
            ++info.frame;
            app.tick(info);
            fps_timer.restart();
        }
    }
}
