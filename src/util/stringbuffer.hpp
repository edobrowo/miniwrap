#pragma once

#include "common.hpp"

TODO("Wide characters");
class StringBuffer {
public:
    StringBuffer();
    ~StringBuffer();

    const char* str();
    std::string toString();

    void put(const char c);
    void putSafe(const char c);
    void append(const char* str, const Size length);
    void append(const std::string& str);

    template <typename... Targs>
    void appendFormat(const char* format_string, Targs... args) {
        format(*this, format_string, args...);
    }

private:
    void expand(const Size size);

    Size m_capacity;
    Index m_next;
    char* m_buffer;

    static constexpr Size INITIAL_CAPACITY = 200;
    static constexpr Size CAPACITY_INCREMENT = 200;
};
