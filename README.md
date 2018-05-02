# C++ I/O library
The library is alternative C++ standard I/O stream library.


## Underconstruction
We will introduce break change.


## Build Environment
- Language version : C++17


## Design
- No Locale (locale is heavy and useless)
- With new line API (`println`)
- Can get native handle (for OS native API)


## Features
- Type specified outputs:
    - unsigned integers
    - signed integer
- Null stream (like `/dev/null`)
- String stream
- Make single header script (`python3 make_single_header.py`)
    - Single header file is committed


## Plan
- More type specified outputs:
    - character
    - string
    - floating point
- Colored output
- String format
- Common interface and adapter


## Example
```cpp
#include <cassert>
#include <cpp_io/io.hpp>

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
```

outputs :

```
123
1111011
7b
0b1111011
0x7b
-123
123
```


## Licence
MIT
