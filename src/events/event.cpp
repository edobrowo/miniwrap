#include "event.hpp"

Event::Event() : m_kind{Kind::Empty}, m_timestamp{0} {}

Event::Event(const Kind kind, const int timestamp)
    : m_kind{kind}, m_timestamp{timestamp} {}

Event::~Event() {}

Event::Kind Event::kind() const noexcept { return m_kind; }

int Event::timestamp() const noexcept { return m_timestamp; }
