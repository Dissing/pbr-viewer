#pragma once

#include "types.h"

#define ERROR(...) error_impl(__FILE__, __LINE__, __VA_ARGS__)

#define ASSERT(cond)                                                                               \
    ((cond) || (error_impl(__FILE__, __LINE__, "'%s' assert failed", #cond), false))

#define UNREACHABLE() ERROR("Unreachable program state in %s!", __func__)

#define NOT_YET_IMPLEMENTED() ERROR("%s() is not yet implemented", __func__)

[[noreturn]] void error_impl(const char* file, uint line, const char* format, ...);
