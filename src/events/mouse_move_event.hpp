#ifndef __MOUSE_MOVE_EVENT__
#define __MOUSE_MOVE_EVENT__

#include "event.hpp"
#include "point.hpp"

class MouseMoveEvent : public Event {
public:
    MouseMoveEvent(const int timestamp, const int x, const int y,
                   const int rel_x, const int rel_y);
    ~MouseMoveEvent();

    Point pos() const noexcept;
    int x() const noexcept;
    int y() const noexcept;

    Point relative() const noexcept;
    int xrel() const noexcept;
    int yrel() const noexcept;

private:
    Point m_position;
    Point m_relative;
};

#endif
