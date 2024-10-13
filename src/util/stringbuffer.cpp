#include "stringbuffer.hpp"

StringBuffer::StringBuffer()
    : m_capacity(INITIAL_CAPACITY),
      m_next(0),
      m_buffer(new char[INITIAL_CAPACITY]) {}

StringBuffer::~StringBuffer() { delete[] m_buffer; }

const char* StringBuffer::str() {
    expand(m_next + 1);
    m_buffer[m_next] = '\0';
    return m_buffer;
}

std::string StringBuffer::toString() {
    const char* s = str();
    return std::string(s);
}

void StringBuffer::put(const char c) { m_buffer[m_next++] = c; }

void StringBuffer::putSafe(const char c) {
    expand(m_next + 1);
    put(c);
}

void StringBuffer::append(const char* str, const Size length) {
    expand(m_next + length);
    std::memcpy(m_buffer + m_next, str, sizeof(char) * length);
    m_next += length;
}

void StringBuffer::append(const std::string& str) {
    expand(m_next + str.size());
    std::memcpy(m_buffer + m_next, str.c_str(), str.size());
    m_next += str.size();
}

void StringBuffer::expand(const Size size) {
    if (size > m_capacity) {
        m_capacity += (size / CAPACITY_INCREMENT + 1) * CAPACITY_INCREMENT;
        char* new_buffer = new char[m_capacity];
        std::memcpy(new_buffer, m_buffer, sizeof(char) * m_next);
        delete[] m_buffer;
        m_buffer = new_buffer;
    }
}
