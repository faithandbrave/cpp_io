#include <cassert>
#include "include/cpp_io/io.hpp"

int main()
{
    using fmt = io::int_format;

    io::println_uint(123u);
    io::println_uint(123u, fmt::binary);
    io::println_uint(123u, fmt::hex);
    io::println_uint(123u, fmt::binary, io::with_prefix);
    io::println_uint(123u, fmt::hex, io::with_prefix);

    io::println_int(-123);
    io::println_int(123);

    // like /dev/null
    io::null_stream null_out;
    io::println_int(null_out, 123); // no output

    // string stream
    io::string_stream ss;
    io::print_int(ss, 123);
    assert(ss.str() == "123");
}
