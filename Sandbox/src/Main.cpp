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
// File Name: Main
// Date File Created: 07/31/2024
// Author: Matt
//
// ------------------------------------------------------------------------------

#include "Argyle.h"
#include "Graphics/Window.h"

#pragma comment(lib, "ArgyleCore.lib")

using namespace argyle;


int main(int argc, char* argv[])
{
    window::window_desc desc = { "Sandbox", 800, 600 };
    if (core::load_modules())
    {
        if (core::graphics_interface().initialize(&desc))
        {
            while (core::graphics_interface().window.is_open())
            {
                core::graphics_interface().window.clear(0.5f, 0.2f, 0.2f, 1.0f);

                core::graphics_interface().render();

                core::graphics_interface().window.swap_buffers();
            }
            core::graphics_interface().shutdown();
        }
    }
    core::unload_modules();
    return 0;
}
