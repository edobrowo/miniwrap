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
    };

    Event();
    Event(const Kind kind, const int timestamp);
    ~Event();

    virtual Kind kind() const noexcept;
    int timestamp() const noexcept;

private:
    Kind m_kind;
    int m_timestamp;
};

#endif
