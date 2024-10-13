#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>

class Timer {
public:
    Timer();

    void start();
    void stop();
    void restart();
    Uint32 ticks() const;
    bool isRunning() const;

private:
    Uint32 m_startTicks;
    bool m_isRunning;
};
