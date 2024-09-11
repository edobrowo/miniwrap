#ifndef __MOUSE_CLICK_EVENT__
#define __MOUSE_CLICK_EVENT__

#include "event.hpp"
#include "event_names.hpp"
#include "point.hpp"

class MouseClickEvent : public Event {
public:
    MouseClickEvent(const int timestamp, const int x, const int y,
                    const MouseButton button, const bool is_pressed,
                    const int click_count);

    ~MouseClickEvent();

    bool isPressed() const noexcept;
    bool isReleased() const noexcept;

    MouseButton button() const noexcept;

    Point pos() const noexcept;
    int x() const noexcept;
    int y() const noexcept;

    int clickCount() const noexcept;
    bool isSingleClick() const noexcept;
    bool isDoubleClick() const noexcept;

private:
    Point m_position;
    MouseButton m_button;
    MouseButtonState m_state;
    int m_clickCount;
};

#endif
