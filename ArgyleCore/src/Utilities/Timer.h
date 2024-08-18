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
// File Name: Timer.h
// Date File Created: 08/17/2024
// Author: Matt
//
// ------------------------------------------------------------------------------

#pragma once

#include "Common.h"

namespace argyle::utl
{
class timer
{
public:
#ifdef _DEBUG
    timer(bool start_now = false, const std::string& name = "unnamed")
#else
    timer(bool start_now = false)
#endif
    {
        if (start_now)
            start();
#ifdef _DEBUG
        m_profiler = start_now;
        m_name     = name;
#endif
    }
    ~timer()
    {
        stop();
#ifdef _DEBUG
        if (m_profiler)
            LOG_INFO("[{}] Profiled scope took {} seconds", m_name, elapsed());
#endif
    }

    void start();
    void stop();
    void reset();
    void accumulate();
    void tick();

    static f64 now();

    constexpr f64 elapsed() const { return m_elapsed_time; }

private:
    f64 m_start_time{};
    f64 m_end_time{};
    f64 m_elapsed_time{};
#ifdef _DEBUG
    bool        m_profiler{};
    std::string m_name{};
#endif
};
} // namespace argyle::utl

#define PROFILE_FUNCTION(func)                                                                                                   \
    argyle::utl::timer timer##__LINE__;                                                                                          \
    timer##__LINE__.start();                                                                                                     \
    {                                                                                                                            \
        func;                                                                                                                    \
    }                                                                                                                            \
    timer##__LINE__.stop();                                                                                                      \
    LOG_INFO("Profiled function: {} took {} seconds", #func, timer##__LINE__.elapsed());

#define PROFILE_SCOPE(name) argyle::utl::timer timer##__LINE__(true, name);
