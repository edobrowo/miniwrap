#include "event.hpp"

class QuitEvent : public Event {
public:
    QuitEvent(const int timestamp);
    ~QuitEvent();
};
