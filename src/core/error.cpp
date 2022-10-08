#include <csignal>
#include <cstdio>
#include <cstdlib>

#include "types.h"

void error_impl(const char* file, uint line, const char* format, ...) {
    va_list args;
    va_start(args, format);

    std::fprintf(stderr, "ABORT: %s:%u\n", file, line);
    std::vfprintf(stderr, format, args);
    std::fprintf(stderr, "\n");
    std::raise(SIGABRT);
    exit(1);
}

#define BACKWARD_HAS_BFD 1
#include <backward.hpp>

namespace backward {

backward::SignalHandling sh;

} // namespace backward
