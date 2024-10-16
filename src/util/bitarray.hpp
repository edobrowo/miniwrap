#pragma once

#include <vector>

#include "common.hpp"

class BitArray {
public:
    BitArray() = default;
    BitArray(const Size num_bits);
    BitArray(const BitArray& other);
    BitArray(const BitArray&& other);
    BitArray& operator=(const BitArray& other);
    BitArray& operator=(BitArray&& other);

    ~BitArray() = default;

    Size bitCount() const;

    bool operator[](const Index i) const;
    void set(const Index i, const bool bit);
    void toggle(const Index i);

    void push(const bool bit);

    void clear();
    void fill();
    void copyFrom(const BitArray& other);

    TODO("logical ops")
    TODO("fixed-size variant")

private:
    std::vector<u64> m_blocks;
    Size m_count;
};
