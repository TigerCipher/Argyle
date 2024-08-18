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
// Date File Created: 08/17/2024
// Author: Matt
//
// ------------------------------------------------------------------------------

#pragma once
#include "Window.h"

#ifdef _DEBUG
    #include "Utilities/Logger.h"
    #include <sstream>
// a bit useless with the error callback, but can be helpful for tracking down errors
// glew must be included before this can be used
    #define GL_CALL(x)                                                                                                           \
        x;                                                                                                                       \
        if (GLenum error##__LINE__ = glGetError(); error##__LINE__ != GL_NO_ERROR)                                               \
        LOG_ERROR("[{}][{}] OpenGL Error: {}, {}", __FILE__, __LINE__, error##__LINE__,                                          \
                  (const char*) glewGetErrorString(error##__LINE__))
#else
    #define GL_CALL(x) x
#endif

namespace argyle::graphics
{
bool init(const window::window_desc& desc);
void shutdown();
void render();

void set_window_title(const std::string& title);
void set_window_size(u32 width, u32 height);

void update_window();

bool is_window_open();

window::window_desc get_window_desc();

namespace gl
{
void clear_color(f32 r, f32 g, f32 b, f32 a = 1.0f);
} // namespace gl
} // namespace argyle::graphics
