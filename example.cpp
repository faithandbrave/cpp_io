#include <cassert>
#include "cpp_io/io.hpp"

int main()
{
    using fmt = io::int_format;

    // output to stdout
    io::println(123u);
    io::println(123u, fmt::binary);
    io::println(123u, fmt::hex);
    io::println(123u, fmt::binary, io::with_prefix);
    io::println(123u, fmt::hex, io::with_prefix);

    io::println(-123);
    io::println(123);

    // like /dev/null
    io::null_stream null_out;
    io::println(null_out, 123); // no output

    // string stream
    io::string_stream ss;
    io::print(ss, 123);
    assert(ss.str() == "123");

    // file stream
    {
        io::scoped_file_stream file;
        file.open("a.txt", "w");
        io::println(file, 123u);
    }
}
