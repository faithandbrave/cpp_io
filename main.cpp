#include <cstdio>
#include <cassert>
#include <limits>
#include <stdexcept>
#include <string>

namespace io {

class file_stream {
    FILE* handle_ = nullptr;
public:
    file_stream() {}
    explicit file_stream(FILE* handle)
        : handle_(handle) {}

    void open(FILE* handle) noexcept {
        handle_ = handle;
    }

    bool open(const char* filename, const char* mode) noexcept {
        handle_ = std::fopen(filename, mode);
        return handle_ != nullptr;
    }

    void close() noexcept {
        if (handle_) {
            std::fclose(handle_);
            handle_ = nullptr;
        }
    }

    FILE* native_handle() noexcept { return handle_; }

    void putc(char c) {
        std::fputc(c, handle_);
    }

    void puts(const char* s) {
        std::fputs(s, handle_);
    }
};

inline file_stream stdout_stream {stdout};
inline file_stream stderr_stream {stderr};

class null_stream {
public:
    void open([[maybe_unused]] FILE* desc) noexcept {}
    bool open([[maybe_unused]] const char* filename, [[maybe_unused]] const char* mode) noexcept { return true; }
    void close() noexcept {}

    void* native_handle() noexcept { return nullptr; }

    void putc([[maybe_unused]] char c) {}
    void puts([[maybe_unused]] const char* s) {}
};

class string_stream {
    std::string buffer_;
public:
    void open([[maybe_unused]] FILE* desc) noexcept {}
    bool open([[maybe_unused]] const char* filename, [[maybe_unused]] const char* mode) noexcept { return true; }
    void close() noexcept {}

    void* native_handle() noexcept { return nullptr; }

    void putc([[maybe_unused]] char c) { buffer_ += c; }
    void puts([[maybe_unused]] const char* s) { buffer_ += s; }

    const std::string& str() const { return buffer_; }
    std::string&& str() { return std::move(buffer_); }
};

template <class OStream, class UInt>
void print_uint(OStream& os, UInt x) {
    print_uint(os, x, 10, false);
}

template <class OStream, class UInt>
void print_uint(OStream& os, UInt x, int base, bool with_prefix=false) {
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

template <class UInt>
void print_uint(UInt x) {
    print_uint(stdout_stream, x);
}

template <class UInt>
void print_uint(UInt x, int base, bool with_prefix=false) {
    print_uint(stdout_stream, x, base, with_prefix);
}

template <class OStream, class UInt>
void println_uint(OStream& os, UInt x) {
    print_uint(os, x);
    os.putc('\n');
}

template <class OStream, class UInt>
void println_uint(OStream& os, UInt x, int base, bool with_prefix=false) {
    print_uint(os, x, base, with_prefix);
    os.putc('\n');
}

template <class UInt>
void println_uint(UInt x) {
    println_uint(stdout_stream, x);
}

template <class UInt>
void println_uint(UInt x, int base, bool with_prefix=false) {
    println_uint(stdout_stream, x, base, with_prefix);
}

static constexpr bool with_prefix = true;

} // namespace io

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
