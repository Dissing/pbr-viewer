#pragma once

#include "types.h"

constexpr inline u64 bitmask(u64 first, u64 last) {
    return (1UL << (last + 1UL)) - (1UL << first);
}

constexpr inline u64 bit(u64 num) {
    return 1ULL << num;
}
