// ------------------------------------------------------------------------------
//
// Argyle
// Copyright 2024 Matthew Rogers
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// File Name: Common.h
// Date File Created: 08/01/2024
// Author: Matt
//
// ------------------------------------------------------------------------------

#pragma once

#define NO_INLINE __declspec(noinline)


// Turns x into a string. Useful for variables, especially in other macros. For example: #define MY_ASSERT(x) LOG(STR_HELPER(x))
// MY_ASSERT(count == 3) would expand to LOG("count == 3")
#define STR_HELPER(x) #x

// Expands a macro to a string. For example: #define MY_MACRO(x) ARGYLE_STRINGIFY_MACRO(x)
// MY_MACRO(__LINE__) would expand to "48" if __LINE__ was 48. Whereas STR_HELPER(__LINE__) would expand to "__LINE__"
#define ARGYLE_STRINGIFY_MACRO(x) STR_HELPER(x)

// Shifts 1 to the left x times. For example: BIT(3) would expand to 0b1000 = 8 = (2^3)
#define BIT(x) (1 << (x))

// Deletes a raw pointer and sets it to null
#define SAFE_DELETE(x)                                                                                                           \
    if (x)                                                                                                                       \
    {                                                                                                                            \
        delete (x);                                                                                                              \
        (x) = nullptr;                                                                                                           \
    }

#ifdef _DEBUG
    // Debug only code
    #define DBG(x) x
#else
    #define DBG(x)
#endif

#ifndef DISABLE_COPY
    // Disables copy constructor and copy assignment operator
    #define DISABLE_COPY(T)                                                                                                      \
        explicit T(const T&)   = delete;                                                                                         \
        T& operator=(const T&) = delete
#endif

#ifndef DISABLE_MOVE
    // Disables move constructor and move assignment operator
    #define DISABLE_MOVE(T)                                                                                                      \
        explicit T(T&&)   = delete;                                                                                              \
        T& operator=(T&&) = delete
#endif

#ifndef DISABLE_COPY_AND_MOVE
    // Disables copy constructor, copy assignment operator, move constructor, and move assignment operator
    #define DISABLE_COPY_AND_MOVE(T)                                                                                             \
        DISABLE_COPY(T);                                                                                                         \
        DISABLE_MOVE(T)

#endif

#ifdef _WIN32
    // Breaks into the debugger
    #define SERT(x) __debugbreak()
#else
    #define SERT(x) assert(x)
#endif

// System includes

#include <cstdint>
#include <memory>
#include <utility>
#include <cassert>
#include <unordered_map>
#include <mutex>

// Argyle includes
#include "Types.h"
#include "Utilities/Logger.h"
#include "Utilities/UUID.h"

#ifdef _DEBUG
    // Asserts that x is true. If x is false, it will log the message and break into the debugger
    #define ARGYLE_ASSERT(x, ...)                                                                                                \
        if (!(x))                                                                                                                \
        {                                                                                                                        \
            argyle::logger::detail::output(                                                                                      \
                argyle::logger::log_level::fatal,                                                                                \
                "Assertion Failed: " ARGYLE_STRINGIFY_MACRO(x) " at line " ARGYLE_STRINGIFY_MACRO(__LINE__) " in " __FILE__);    \
            argyle::logger::detail::output(argyle::logger::log_level::fatal, __VA_ARGS__);                                       \
            SERT((x));                                                                                                           \
        }
#else
    #define ARGYLE_ASSERT(x, ...)
#endif
