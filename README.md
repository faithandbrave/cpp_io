# C++ I/O library
The library is alternative C++ standard I/O stream library.


## Underconstruction
We will introduce break change.


## Deign
- No Locale (locale is heavy and useless)
- With new line API (`println`)
- Can get native handle (for OS native API)


## Plan
- Null stream (like `/dev/null`)
- String stream
- String format
- Common interface and adapter


## API
```cpp
namespace io {
  // unscoped
  class file_descriptor {
    void open(FILE* desc) noexcept;
    bool open(const char* filename, const char* mode) noexcept;

    void close() noexcept;

    FILE* native_handle();

    template <class UInt>
    void print_uint(UInt x);
    template <class UInt>
    void print_uint(UInt x, int base, bool with_prefix=false);

    // with new line
    template <class UInt>
    void println_uint(UInt x);
    template <class UInt>
    void println_uint(UInt x, int base, bool with_prefix=false);
  };

  static constexpr bool with_prefix = true;
}
```


## Example
```cpp
int main()
{
    io::file_descriptor file;
    file.open(stdout);
    file.println_uint(123u);
    file.println_uint(123u, 2);
    file.println_uint(123u, 16);
    file.println_uint(123u, 2, io::with_prefix);
    file.println_uint(123u, 16, io::with_prefix);
}
```

outputs :

```
123
1111011
7b
0b1111011
0x7b
```


## Licence
MIT
