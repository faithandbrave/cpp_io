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

} // namespace io
