#include <beast_http/common/error_code.hpp>

#include <fmt/core.h>
using fmt::print;

#include <beast_http/common/common.hpp>

BEAST_HTTP_BEGIN_NAMESPACE
[[nodiscard]] error_category const& get_error_category() noexcept
{
    static error_category error_category_instance;
    return error_category_instance;
}

void test_error_code()
{
    std::error_code ec = beast_http::error_code::file_error;
    print("value: {}, message: {}.\n", ec.value(), ec.message());
}
BEAST_HTTP_END_NAMESPACE