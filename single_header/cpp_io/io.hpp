#pragma once

#include <cstdio>

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

} // namespace io

namespace io {

class null_stream {
public:
    void putc([[maybe_unused]] char c) {}
    void puts([[maybe_unused]] const char* s) {}
};

} // namespace io

#include <string>

namespace io {

class string_stream {
    std::string buffer_;
public:
    void putc([[maybe_unused]] char c) { buffer_ += c; }
    void puts([[maybe_unused]] const char* s) { buffer_ += s; }

    const std::string& str() const { return buffer_; }
    std::string&& str() { return std::move(buffer_); }
};

} // namespace io

namespace io {

enum int_format {
    decimal = 10,
    hex = 16,
    binary = 2
};

} // namespace io

#include <cstdlib>
#include <type_traits>

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

#include <stdexcept>
#include <limits>

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



namespace io {

inline constexpr bool with_prefix = true;

} // namespace io
