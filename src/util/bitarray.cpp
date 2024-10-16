#include "bitarray.hpp"

#include <memory>

#include "math.hpp"

BitArray::BitArray(const Size num_bits)
    : m_blocks(math::divceil(num_bits, Size(64)), 0), m_count(num_bits) {}

BitArray::BitArray(const BitArray& other)
    : m_blocks(other.m_blocks), m_count(other.m_count) {}

BitArray::BitArray(const BitArray&& other)
    : m_blocks(std::move(other.m_blocks)), m_count(other.m_count) {}

BitArray& BitArray::operator=(const BitArray& other) {
    m_blocks = other.m_blocks;
    m_count = other.m_count;
    return *this;
}

BitArray& BitArray::operator=(BitArray&& other) {
    m_blocks = std::move(other.m_blocks);
    m_count = other.m_count;
    return *this;
}

Size BitArray::bitCount() const { return m_count; }

bool BitArray::operator[](const Index i) const {
    assert(i < m_count);
    return (m_blocks[i / 64] >> (i % 64)) & u64(0b1);
}

void BitArray::set(const Index i, const bool bit) {
    assert(i < m_count);
    m_blocks[i / 64] = (m_blocks[i / 64] & ~(u64(0b1) << (i % 64))) |
                       (u64(bit > 0) << (i % 64));
}

void BitArray::toggle(const Index i) {
    assert(i < m_count);
    m_blocks[i / 64] ^= (u64(0b1) << (i % 64));
}

void BitArray::push(const bool bit) {
    if ((m_count + 1) / 64 > m_blocks.size()) {
        m_blocks.push_back(0);
    }
    set(m_count++, bit);
}

void BitArray::clear() {
    std::memset(m_blocks.data(), 0, m_blocks.size() * sizeof(u64));
}

void BitArray::fill() {
    std::memset(m_blocks.data(), 0xFF, m_blocks.size() * sizeof(u64));
}

void BitArray::copyFrom(const BitArray& other) {
    assert(m_blocks.size() == other.m_blocks.size());
    std::memcpy(m_blocks.data(), other.m_blocks.data(),
                m_blocks.size() * sizeof(u64));
}
