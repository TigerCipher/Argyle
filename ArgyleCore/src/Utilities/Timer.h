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
    timer() = default;
    ~timer() = default;

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
};
} // namespace argyle::utl
