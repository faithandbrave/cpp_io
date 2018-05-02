#pragma once

#include <stdexcept>
#include <limits>
#include "format.hpp"

namespace io {

template <class OStream, class UInt>
void print_uint(OStream& os, UInt x, int_format fmt, bool with_prefix=false) {
    const int base = static_cast<int>(fmt);
    if (!(base == 2 || base == 10 || base == 16))
        throw std::invalid_argument("integer base must be 2 or 10 or 16");

    if (with_prefix) {
        if (base == 2) {
            os.puts("0b");
        }
        else if (base == 16) {
            os.puts("0x");
        }
    }

    if (x == 0) {
        os.putc('0');
        return;
    }

    const char table[] = "0123456789abcdef";
    constexpr int digits = std::numeric_limits<UInt>::digits10;
    char str[digits + 1] = {0};
    char* p = str + digits;

    UInt y = x;
    do {
        UInt div = y / base;
        UInt mod = y % base;

        *--p = table[mod];

        y = div;
    }
    while (y != 0);

    os.puts(p);
}

template <class OStream, class UInt>
void print_uint(OStream& os, UInt x) {
    print_uint(os, x, int_format::decimal, false);
}

template <class UInt>
void print_uint(UInt x) {
    print_uint(stdout_stream, x);
}

template <class UInt>
void print_uint(UInt x, int_format fmt, bool with_prefix=false) {
    print_uint(stdout_stream, x, fmt, with_prefix);
}

template <class OStream, class UInt>
void println_uint(OStream& os, UInt x) {
    print_uint(os, x);
    os.putc('\n');
}

template <class OStream, class UInt>
void println_uint(OStream& os, UInt x, int_format fmt, bool with_prefix=false) {
    print_uint(os, x, fmt, with_prefix);
    os.putc('\n');
}

template <class UInt>
void println_uint(UInt x) {
    println_uint(stdout_stream, x);
}

template <class UInt>
void println_uint(UInt x, int_format fmt, bool with_prefix=false) {
    println_uint(stdout_stream, x, fmt, with_prefix);
}

} // namespace io
