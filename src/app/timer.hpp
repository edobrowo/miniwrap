#pragma once

#include "common.hpp"

class Timer {
public:
    Timer();

    void start();
    void stop();
    void restart();
    u64 elapsed() const;
    bool isRunning() const;

private:
    u64 m_startMs;
    bool m_isRunning;
};
