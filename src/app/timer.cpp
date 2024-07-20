#include "timer.hpp"

Timer::Timer() : m_startTicks{0}, m_isRunning{false} {}

void Timer::start() {
    m_isRunning = true;
    m_startTicks = SDL_GetTicks();
}

void Timer::stop() {
    m_isRunning = false;
}

void Timer::restart() {
    start();
}

Uint32 Timer::ticks() const {
    if (!m_isRunning) {
        return 0;
    }
    return SDL_GetTicks() - m_startTicks;
}

bool Timer::isRunning() const {
    return m_isRunning;
}
