// The file is auto generated. DO NOT edit the file directly.
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


class scoped_file_stream {
    file_stream stream_;
public:
    scoped_file_stream() {}
    explicit scoped_file_stream(FILE* handle)
        : stream_(handle) {}

    ~scoped_file_stream() {
        close();
    }

    void open(FILE* handle) noexcept {
        stream_.open(handle);
    }

    bool open(const char* filename, const char* mode) noexcept {
        return stream_.open(filename, mode);
    }

    void close() noexcept {
        stream_.close();
    }

    FILE* native_handle() noexcept { return stream_.native_handle(); }

    void putc(char c) {
        stream_.putc(c);
    }

    void puts(const char* s) {
        stream_.puts(s);
    }
};

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

#include <type_traits>

namespace io {

template <class>
struct is_stream : std::false_type {};

template <> struct is_stream<file_stream> : std::true_type {};
template <> struct is_stream<null_stream> : std::true_type {};
template <> struct is_stream<string_stream> : std::true_type {};

template <class T>
constexpr bool is_stream_v = is_stream<T>::value;

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

} // namespace io

#include <type_traits>

namespace io {

template <class OStream, class T, class... Options>
std::enable_if_t<is_stream_v<OStream>> print(OStream& os, T&& x, Options&&... options) {
    if constexpr (std::is_integral_v<T>) {
        if constexpr (std::is_unsigned_v<T>) {
            print_uint(os, std::move(x), std::move(options)...);
        }
        else {
            print_int(os, std::move(x), std::move(options)...);
        }
    }
}

template <class T, class... Options>
std::enable_if_t<!is_stream_v<T>> print(T&& x, Options&&... options) {
    print(stdout_stream, std::move(x), std::move(options)...);
}

template <class OStream, class... Args>
std::enable_if_t<is_stream_v<OStream>> println(OStream& os, Args&&... args) {
    print(os, std::move(args)...);
    os.putc('\n');
}

template <class Head, class... Args>
std::enable_if_t<!is_stream_v<Head>> println(Head&& head, Args&&... args) {
    print(stdout_stream, std::move(head), std::move(args)...);
    stdout_stream.putc('\n');
}

}




namespace io {

inline constexpr bool with_prefix = true;

} // namespace io
