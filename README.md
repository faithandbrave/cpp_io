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
    - now only unsigned integers
- Null stream (like `/dev/null`)
- String stream


## Plan
- String format
- Common interface and adapter


## API
```cpp
namespace io {
  // stream classes
  class file_stream {
  public:
    file_stream() {}
    explicit file_stream(FILE* handle);

    void open(FILE* handle) noexcept;
    bool open(const char* filename, const char* mode) noexcept;
    void close() noexcept;

    FILE* native_handle() noexcept;

    void putc(char c);
    void puts(const char* s);
  };

  inline file_stream stdout_stream {stdout};
  inline file_stream stderr_stream {stderr};

  class null_stream {
  public:
    void open(FILE*) noexcept;
    bool open(const char*, const char*) noexcept;
    void close() noexcept;

    void* native_handle() noexcept;

    void putc(char);
    void puts(const char*);
  };

  class string_stream {
  public:
    void open(FILE*) noexcept;
    bool open(const char*, const char*) noexcept;
    void close() noexcept;

    void* native_handle() noexcept;

    void putc(char c);
    void puts(const char* s);

    const std::string& str() const;
    std::string&& str();
  };

  // output APIs
  template <class OStream, class UInt>
  void print_uint(OStream& os, UInt x);
  template <class OStream, class UInt>
  void print_uint(OStream& os, UInt x, int base, bool with_prefix=false);

  template <class UInt>
  void print_uint(UInt x);
  template <class UInt>
  void print_uint(UInt x, int base, bool with_prefix=false);

  // with new line
  template <class OStream, class UInt>
  void println_uint(OStream& os, UInt x);
  template <class OStream, class UInt>
  void println_uint(OStream& os, UInt x, int base, bool with_prefix=false);
  template <class UInt>
  void println_uint(UInt x);
  template <class UInt>
  void println_uint(UInt x, int base, bool with_prefix=false);

  static constexpr bool with_prefix = true;
}
```


## Example
```cpp
int main()
{
    io::println_uint(123u);
    io::println_uint(123u, 2);
    io::println_uint(123u, 16);
    io::println_uint(123u, 2, io::with_prefix);
    io::println_uint(123u, 16, io::with_prefix);

    // like /dev/null
    io::null_stream null_out;
    io::println_uint(null_out, 123u); // no output

    // string stream
    io::string_stream ss;
    io::print_uint(ss, 123u);
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
```


## Licence
MIT
