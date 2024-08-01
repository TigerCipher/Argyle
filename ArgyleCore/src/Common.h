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
// File Name: Common.h
// Date File Created: 08/01/2024
// Author: Matt
//
// ------------------------------------------------------------------------------

#pragma once

#define NO_INLINE __declspec(noinline)

#define ARGYLE_EXPAND_MACRO(x)    x
#define ARGYLE_STRINGIFY_MACRO(x) #x

#define BIT(x) (1 << (x))

#define SAFE_DELETE(x)                                                                                                           \
    if (x)                                                                                                                       \
    {                                                                                                                            \
        delete (x);                                                                                                              \
        (x) = nullptr;                                                                                                           \
    }

#ifdef _DEBUG
    #define DBG(x) x
#else
    #define DBG(x)
#endif

#ifndef DISABLE_COPY
    #define DISABLE_COPY(T)                                                                                                      \
        explicit T(const T&)   = delete;                                                                                         \
        T& operator=(const T&) = delete
#endif

#ifndef DISABLE_MOVE
    #define DISABLE_MOVE(T)                                                                                                      \
        explicit T(T&&)   = delete;                                                                                              \
        T& operator=(T&&) = delete
#endif

#ifndef DISABLE_COPY_AND_MOVE
    #define DISABLE_COPY_AND_MOVE(T)                                                                                             \
        DISABLE_COPY(T);                                                                                                         \
        DISABLE_MOVE(T)

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