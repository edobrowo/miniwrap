#include "timer.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>

#include "format.hpp"

Timer::Timer()
    : m_startMs(0), m_pausedMs(0), m_isStarted(false), m_isPaused(false) {}

void Timer::start() {
    m_isStarted = true;
    m_isPaused = false;
    m_startMs = SDL_GetTicks64();
    m_pausedMs = 0;
}

void Timer::stop() {
    m_isStarted = false;
    m_isPaused = false;
    m_startMs = 0;
    m_pausedMs = 0;
}

void Timer::restart() { start(); }

void Timer::pause() {
    if (m_isStarted && !m_isPaused) {
        m_isPaused = true;
        m_pausedMs = SDL_GetTicks64() - m_startMs;
        m_startMs = 0;
    }
}

void Timer::unpause() {
    if (m_isStarted && m_isPaused) {
        m_isPaused = false;
        m_startMs = SDL_GetTicks64() - m_pausedMs;
        m_pausedMs = 0;
    }
}

void Timer::toggle() {
    if (m_isStarted) {
        if (!m_isPaused)
            pause();
        else
            unpause();
    }
}

u64 Timer::elapsed() const {
    if (!m_isStarted)
        return 0;
    if (m_isPaused)
        return m_pausedMs;
    return SDL_GetTicks64() - m_startMs;
}

bool Timer::isStarted() const { return m_isStarted; }

bool Timer::isPaused() const { return m_isPaused && m_isStarted; }
