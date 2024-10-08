﻿// ------------------------------------------------------------------------------
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
// File Name: Types.h
// Date File Created: 08/01/2024
// Author: Matt
//
// ------------------------------------------------------------------------------

#pragma once
#include <cstdint>
#include <memory>
#include <string>

// Types and shortcuts

using ulong = unsigned long;

// ensure x bit, but I hate using _t, it looks ugly
using u8  = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

using i8  = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;


constexpr u8  invalid_id_u8  = 0xffui8;
constexpr u16 invalid_id_u16 = 0xffffui16;
constexpr u32 invalid_id_u32 = 0xffff'ffffui32;
constexpr u64 invalid_id_u64 = 0xffff'ffff'ffff'ffffui64;


using f32 = float;
using f64 = double;


using string_hash = std::hash<std::string>;


template<typename T>
using uptr = std::unique_ptr<T>;

template<typename T>
using sptr = std::shared_ptr<T>;



template<typename T, typename... Args>
constexpr uptr<T> create_uptr(Args&&... args)
{
    return std::make_unique<T>(std::forward<Args>(args)...);
}

template<typename T, typename... Args>
constexpr sptr<T> create_sptr(Args&&... args)
{
    return std::make_shared<T>(std::forward<Args>(args)...);
}

inline auto operator""_KB(const size_t x)
{
    return x * 1024u;
}
inline auto operator""_MB(const size_t x)
{
    // x * 1024 * 1024
    return x * 1048576u;
}
inline auto operator""_GB(const size_t x)
{
    // x * 1024 * 1024 * 1024
    return x * 1073741824u;
}

inline u32 operator""_KBu(const size_t x)
{
    return (u32) x * 1024u;
}
inline u32 operator""_MBu(const size_t x)
{
    // x * 1024 * 1024
    return (u32) x * 1048576u;
}
inline u32 operator""_GBu(const size_t x)
{
    // x * 1024 * 1024 * 1024
    return (u32) x * 1073741824u;
}