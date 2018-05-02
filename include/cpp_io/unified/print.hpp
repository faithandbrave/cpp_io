#pragma once

#include <type_traits>
#include "../stream/file.hpp"
#include "../traits/is_stream.hpp"
#include "../print/uint.hpp"
#include "../print/sint.hpp"

namespace io {
    template <class OStream, class T, class... Options>
    std::enable_if_t<is_stream_v<OStream>> print(OStream& os, const T& x, Options&&... options) {
        if constexpr (std::is_integral_v<T>) {
            if constexpr (std::is_unsigned_v<T>) {
                print_uint(os, x, std::move(options)...);
            }
            else {
                print_int(os, x, std::move(options)...);
            }
        }
    }

    template <class OStream, class T, class... Options>
    std::enable_if_t<!is_stream_v<T>> print(const T& x, Options&&... options) {
        if constexpr (std::is_integral_v<T>) {
            if constexpr (std::is_unsigned_v<T>) {
                print_uint(stdout_stream, x, std::move(options)...);
            }
            else {
                print_int(stdout_stream, x, std::move(options)...);
            }
        }
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
