#pragma once

#include "common.hpp"
#include "event.hpp"

class QuitEvent : public Event {
public:
    QuitEvent(const u64 timestamp);
};
