#pragma once

#include <string>
#include <spdlog/spdlog.h>
#include <beast_http/common/common.hpp>

BEAST_HTTP_BEGIN_NAMESPACE
BEAST_HTTP_EXPORT
void set_default_log(std::string const& log_path = "./logs/log.txt", std::string const& log_name = "beast_http", spdlog::level::level_enum level = spdlog::level::info);

BEAST_HTTP_EXPORT
void change_default_log_level(spdlog::level::level_enum level);
BEAST_HTTP_END_NAMESPACE
