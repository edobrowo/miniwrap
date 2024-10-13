#pragma once

#include "common.hpp"

class Event {
public:
    enum class Kind {
        Empty = 0,

        MouseClick = 100,
        MouseMove,
        MouseScroll,

        Keyboard = 200,

        Quit = 300,
    };

    Kind kind;
    u64 timestamp;

    Event();
    Event(const Kind kind, const u64 timestamp);
    virtual ~Event();
};
