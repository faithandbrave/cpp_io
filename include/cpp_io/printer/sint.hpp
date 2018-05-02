#pragma once

#include <cstdlib>
#include <type_traits>
#include "uint.hpp"

namespace io {

template <class OStream, class SInt>
void print_int(OStream& os, SInt x, int_format fmt, bool with_prefix=false) {
    if (x < 0) {
        os.putc('-');
    }

    print_uint(os, static_cast<std::make_unsigned_t<SInt>>(abs(x)), fmt, with_prefix);
}

template <class OStream, class SInt>
void print_int(OStream& os, SInt x) {
    print_int(os, x, int_format::decimal, false);
}

template <class SInt>
void print_int(SInt x) {
    print_int(stdout_stream, x);
}

template <class SInt>
void print_int(SInt x, int_format fmt, bool with_prefix=false) {
    print_int(stdout_stream, x, fmt, with_prefix);
}

template <class OStream, class SInt>
void println_int(OStream& os, SInt x) {
    print_int(os, x);
    os.putc('\n');
}

template <class OStream, class SInt>
void println_int(OStream& os, SInt x, int_format fmt, bool with_prefix=false) {
    print_int(os, x, fmt, with_prefix);
    os.putc('\n');
}

template <class SInt>
void println_int(SInt x) {
    println_int(stdout_stream, x);
}

template <class SInt>
void println_int(SInt x, int_format fmt, bool with_prefix=false) {
    println_int(stdout_stream, x, fmt, with_prefix);
}

} // namespace io
