#include "event.hpp"

Event::Event() : kind(Kind::Empty), timestamp(0) {}

Event::Event(const Kind kind, const u64 timestamp)
    : kind(kind), timestamp(timestamp) {}

Event::~Event() {}
