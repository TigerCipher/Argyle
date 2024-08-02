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
// File Name: GLInterface
// Date File Created: 08/01/2024
// Author: Matt
//
// ------------------------------------------------------------------------------
#include "GLInterface.h"

#include "GLCore.h"

using namespace argyle;


void get_graphics_interface(argyle::graphics::graphics_interface& gfx_interface)
{
    gfx_interface.initialize = gl::core::init;

    gfx_interface.shutdown = gl::core::shutdown;

    gfx_interface.window.swap_buffers = gl::core::update_window;
    gfx_interface.window.clear        = gl::clear_color;
    gfx_interface.window.is_open      = gl::core::is_window_open;
}