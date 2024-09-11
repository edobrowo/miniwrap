#include "quit_event.hpp"

QuitEvent::QuitEvent(const int timestamp)
    : Event{Event::Kind::Quit, timestamp} {}

QuitEvent::~QuitEvent() {}
