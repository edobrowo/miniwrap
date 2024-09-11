#ifndef __EVENT__
#define __EVENT__

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

    Event();
    Event(const Kind kind, const int timestamp);
    virtual ~Event();

    virtual Kind kind() const noexcept;
    int timestamp() const noexcept;

private:
    Kind m_kind;
    int m_timestamp;
};

#endif
