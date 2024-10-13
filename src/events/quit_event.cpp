#include "quit_event.hpp"

QuitEvent::QuitEvent(const u64 timestamp)
    : Event(Event::Kind::Quit, timestamp) {}
