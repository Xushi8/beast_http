#pragma once

#include <string_view>
#include <cstddef>
#include <boost/container/string.hpp>
#include <beast_http/common/common.hpp>

BEAST_HTTP_BEGIN_NAMESPACE
BEAST_HTTP_EXPORT
boost::container::string base64_encode(std::string_view input);
BEAST_HTTP_EXPORT
boost::container::string base64_encode(const void* input, size_t len);

BEAST_HTTP_EXPORT
boost::container::string base64_decode(std::string_view input);
BEAST_HTTP_EXPORT
boost::container::string base64_decode(const char* input, size_t len);
BEAST_HTTP_END_NAMESPACE
