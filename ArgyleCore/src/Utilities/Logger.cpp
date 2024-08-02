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
#include "Logger.h"

namespace argyle::logger::detail
{

void output(const log_level::level lvl, std::string_view message)
{
    std::string str;
    switch (lvl)
    {
    case log_level::debug: str = std::format("[ DEBUG ]: {}\n", message); break;
    case log_level::info: str = std::format("[ INFO ]: {}\n", message); break;
    case log_level::warn: str = std::format("[ WARNING ]: {}\n", message); break;
    case log_level::error: str = std::format("[ ERROR ]: {}\n", message); break;
    case log_level::fatal: str = std::format("[ FATAL ]: {}\n", message); break;
    }

#ifdef _WINDOWS
    OutputDebugStringA(str.c_str());
#else
    printf("%s", str.c_str());
#endif
}


} // namespace argyle::logger::detail