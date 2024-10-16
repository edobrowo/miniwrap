#pragma once

#include "common.hpp"

// https://lazyfoo.net/tutorials/SDL/23_advanced_timers/index.php
class Timer {
public:
    Timer();

    void start();
    void stop();
    void restart();

    void pause();
    void unpause();
    void toggle();

    u64 elapsed() const;
    bool isStarted() const;
    bool isPaused() const;

private:
    u64 m_startMs;
    u64 m_pausedMs;
    bool m_isStarted;
    bool m_isPaused;
};
