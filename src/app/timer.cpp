#include "timer.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>

Timer::Timer() : m_startMs{0}, m_isRunning(false) {}

void Timer::start() {
    m_isRunning = true;
    m_startMs = SDL_GetTicks64();
}

void Timer::stop() { m_isRunning = false; }

void Timer::restart() { start(); }

u64 Timer::elapsed() const {
    if (!m_isRunning) {
        return 0;
    }
    return SDL_GetTicks64() - m_startMs;
}

bool Timer::isRunning() const { return m_isRunning; }
