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
