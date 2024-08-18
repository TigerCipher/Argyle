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

#include "Timer.h"
#include <GLFW/glfw3.h>

namespace argyle::utl
{


void timer::start()
{
    m_start_time = glfwGetTime();
}

void timer::stop()
{
    m_end_time = glfwGetTime();
    m_elapsed_time = m_end_time - m_start_time;
}

void timer::reset()
{
    m_start_time   = 0.0;
    m_end_time     = 0.0;
    m_elapsed_time = 0.0;
    start();
}

void timer::accumulate()
{
    m_end_time = glfwGetTime();
    m_elapsed_time += m_end_time - m_start_time;
    m_start_time = m_end_time;
}


} // namespace argyle::utl