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
// File Name: GLCore.h
// Date File Created: 08/01/2024
// Author: Matt
//
// ------------------------------------------------------------------------------

#pragma once
#include "Graphics/Window.h"

#define GLFW_WINDOW_FROM_HANDLE (GLFWwindow*) gl::core::get_window_desc()->handle

namespace argyle::gl
{

namespace core
{
bool init(window::window_desc* desc);
void shutdown();

// Swaps buffers and polls events
void update_window();

bool is_window_open();

window::window_desc* get_window_desc();
} // namespace core

void clear_color(f32 r, f32 g, f32 b, f32 a = 1.0f);

} // namespace argyle::gl