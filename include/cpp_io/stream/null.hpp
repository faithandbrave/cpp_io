#pragma once

namespace io {

class null_stream {
public:
    void putc([[maybe_unused]] char c) {}
    void puts([[maybe_unused]] const char* s) {}
};

} // namespace io
