#ifndef __MOUSE_SCROLL_EVENT__
#define __MOUSE_SCROLL_EVENT__

#include "event.hpp"
#include "event_names.hpp"
#include "point.hpp"

class MouseScrollEvent : public Event {
public:
    MouseScrollEvent(
        const int timestamp,
        const int x,
        const int y,
        const mouse::ScrollDirection direction,
        const float scroll_horizontal,
        const float scroll_vertical);
    ~MouseScrollEvent();

    Point pos() const noexcept;
    int x() const noexcept;
    int y() const noexcept;

    float horizontal() const noexcept;
    float vertical() const noexcept;

private:
    Point m_position;
    mouse::ScrollDirection m_direction;
    float m_horizontal;
    float m_vertical;
};

#endif
