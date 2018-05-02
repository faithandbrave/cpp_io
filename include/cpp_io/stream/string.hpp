#pragma once

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
