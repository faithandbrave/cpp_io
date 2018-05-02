#pragma once

#include <type_traits>
#include "../stream/file.hpp"
#include "../stream/null.hpp"
#include "../stream/string.hpp"

namespace io {

template <class>
struct is_stream : std::false_type {};

template <> struct is_stream<file_stream> : std::true_type {};
template <> struct is_stream<null_stream> : std::true_type {};
template <> struct is_stream<string_stream> : std::true_type {};

template <class T>
constexpr bool is_stream_v = is_stream<T>::value;

} // namespace io
