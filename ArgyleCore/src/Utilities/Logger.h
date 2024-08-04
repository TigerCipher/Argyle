// ------------------------------------------------------------------------------
//
// Argyle
//    Copyright 2024 Matthew Rogers
//
//    Licensed under the Apache License, Version 2.0 (the "License");
//    you may not use this file except in compliance with the License.
//    You may obtain a copy of the License at
//
//        http://www.apache.org/licenses/LICENSE-2.0
//
//    Unless required by applicable law or agreed to in writing, software
//    distributed under the License is distributed on an "AS IS" BASIS,
//    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//    See the License for the specific language governing permissions and
//    limitations under the License.
//
// File Name: Logger
// Date File Created: 08/01/2024
// Author: Matt
//
// ------------------------------------------------------------------------------

#pragma once

#include "Types.h"

#include <format>

namespace argyle::logger
{

struct log_level
{
    enum level : u8
    {
        debug,
        info,
        warn,
        error,
        fatal,
    };
};

namespace detail
{
void output(log_level::level lvl, std::string_view message);
} // namespace detail

} // namespace argyle::logger

#if defined(_DEBUG)
    #define LOG_DEBUG(msg, ...) argyle::logger::detail::output(argyle::logger::log_level::debug, std::format(msg, ##__VA_ARGS__))
    #define LOG_INFO(msg, ...)  argyle::logger::detail::output(argyle::logger::log_level::info, std::format(msg, ##__VA_ARGS__))
    #define LOG_WARN(msg, ...)  argyle::logger::detail::output(argyle::logger::log_level::warn, std::format(msg, ##__VA_ARGS__))
    #define LOG_ERROR(msg, ...) argyle::logger::detail::output(argyle::logger::log_level::error, std::format(msg, ##__VA_ARGS__))
    #define LOG_FATAL(msg, ...) argyle::logger::detail::output(argyle::logger::log_level::fatal, std::format(msg, ##__VA_ARGS__))
#elif defined(ARGYLE_ENABLE_LOGGING) && defined(LOG_LEVEL_ALL)
    #define LOG_DEBUG(msg, ...)
    #define LOG_INFO(msg, ...)  argyle::logger::detail::output(argyle::logger::log_level::info, std::format(msg, ##__VA_ARGS__))
    #define LOG_WARN(msg, ...)  argyle::logger::detail::output(argyle::logger::log_level::warn, std::format(msg, ##__VA_ARGS__))
    #define LOG_ERROR(msg, ...) argyle::logger::detail::output(argyle::logger::log_level::error, std::format(msg, ##__VA_ARGS__))
    #define LOG_FATAL(msg, ...) argyle::logger::detail::output(argyle::logger::log_level::fatal, std::format(msg, ##__VA_ARGS__))
#elif defined(ARGYLE_ENABLE_LOGGING) && defined(LOG_LEVEL_WARN)
    #define LOG_DEBUG(msg, ...)
    #define LOG_INFO(msg, ...)
    #define LOG_WARN(msg, ...)  argyle::logger::detail::output(argyle::logger::log_level::warn, std::format(msg, ##__VA_ARGS__))
    #define LOG_ERROR(msg, ...) argyle::logger::detail::output(argyle::logger::log_level::error, std::format(msg, ##__VA_ARGS__))
    #define LOG_FATAL(msg, ...) argyle::logger::detail::output(argyle::logger::log_level::fatal, std::format(msg, ##__VA_ARGS__))
#elif defined(ARGYLE_ENABLE_LOGGING) && defined(LOG_LEVEL_ERROR)
    #define LOG_DEBUG(msg, ...)
    #define LOG_INFO(msg, ...)
    #define LOG_WARN(msg, ...)
    #define LOG_ERROR(msg, ...) argyle::logger::detail::output(argyle::logger::log_level::error, std::format(msg, ##__VA_ARGS__))
    #define LOG_FATAL(msg, ...) argyle::logger::detail::output(argyle::logger::log_level::fatal, std::format(msg, ##__VA_ARGS__))
#else
    #define LOG_DEBUG(msg, ...)
    #define LOG_INFO(msg, ...)
    #define LOG_WARN(msg, ...)
    #define LOG_ERROR(msg, ...)
    #define LOG_FATAL(msg, ...)
#endif