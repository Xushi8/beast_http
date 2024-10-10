#pragma once

#include <beast_http/common/common.hpp>
#include <string>
#include <system_error>
#include <cstddef>

BEAST_HTTP_BEGIN_NAMESPACE
BEAST_HTTP_EXPORT
std::error_code create_reserve_file(std::string const& file_name, size_t len);
BEAST_HTTP_END_NAMESPACE