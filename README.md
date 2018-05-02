# C++ I/O library
The library is alternative C++ standard I/O stream library.


## Underconstruction
We will introduce break change.


## Deign
- No Locale (locale is heavy and useless)
- With new line API (`println`)
- Can get native handle (for OS native API)


## Plan
- null stream (like `/dev/null`)
- string stream
- string format
- common interface and adapter


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
    void print_uint(UInt x, int base, bool with_prefix=false)

    // with new line
    template <class UInt>
    void println_uint(UInt x);
  };

  static constexpr bool with_prefix = true;
}
```
