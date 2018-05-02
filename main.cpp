#include <cstdio>
#include <cassert>
#include <limits>
#include <stdexcept>

namespace io {

class file_descriptor {
    FILE* desc_ = nullptr;
public:
    void open(FILE* desc) noexcept {
        desc_ = desc;
    }

    bool open(const char* filename, const char* mode) noexcept {
        desc_ = std::fopen(filename, mode);
        return desc_ != nullptr;
    }

    void close() noexcept {
        if (desc_) {
            std::fclose(desc_);
            desc_ = nullptr;
        }
    }

    FILE* native_handle() { return desc_; }

    template <class UInt>
    void print_uint(UInt x) {
        print_uint(x, 10, false);
    }

    template <class UInt>
    void print_uint(UInt x, int base, bool with_prefix=false) {
        if (!(base == 2 || base == 10 || base == 16))
            throw std::invalid_argument("integer base must be 2 or 10 or 16");

        if (with_prefix) {
            if (base == 2) {
                std::fputs("0b", desc_);
            }
            else if (base == 16) {
                std::fputs("0x", desc_);
            }
        }

        if (x == 0) {
            std::fputc('0', desc_);
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

        std::fputs(p, desc_);
    }

    template <class UInt>
    void println_uint(UInt x) {
        print_uint(x);
        std::fputc('\n', desc_);
    }

    template <class UInt>
    void println_uint(UInt x, int base, bool with_prefix=false) {
        print_uint(x, base, with_prefix);
        std::fputc('\n', desc_);
    }
};

static constexpr bool with_prefix = true;

} // namespace io

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
