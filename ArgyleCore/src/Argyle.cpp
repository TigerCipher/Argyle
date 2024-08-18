﻿// ------------------------------------------------------------------------------
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
// File Name: Argyle
// Date File Created: 07/31/2024
// Author: Matt
//
// ------------------------------------------------------------------------------
#include "Argyle.h"
#include "Graphics/Window.h"
#include "Utilities/Timer.h"

#define RENDERER_DLL "GLRenderer.dll"

namespace argyle::core
{

bool load_modules()
{
    return load_renderer(RENDERER_DLL);
}

void unload_modules()
{
    unload_renderer();
}

bool init(const char* title, u32 width, u32 size)
{
    LOG_INFO("Initializing Argyle Core");
    return graphics::init({ title, width, size });
}

void run()
{
    utl::timer frame_timer;
    utl::timer seconds;
    seconds.start();
    u32 frames = 0;
    std::string orig_title = graphics::get_window_desc().title;
    while(graphics::is_window_open())
    {
        seconds.accumulate();
        frame_timer.start();
        graphics::gl::clear_color(0.5f, 0.2f, 0.2f, 1.0f);
        graphics::render();
        graphics::update_window();
        ++frames;
        frame_timer.stop();
        f64 fps = 1.0f / frame_timer.elapsed();
        if(seconds.elapsed() >= 1.0)
        {
            std::string title = std::format("{} | FPS: {}", orig_title, frames);
            graphics::set_window_title(title);
            LOG_DEBUG("FPS: {}, Average FPS: {}", frames, fps);
            seconds.reset();
            frames = 0;
        }
    }
}

void shutdown()
{
    graphics::shutdown();
}

} // namespace argyle::core