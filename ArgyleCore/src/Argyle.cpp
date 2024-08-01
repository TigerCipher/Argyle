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
// File Name: Argyle
// Date File Created: 07/31/2024
// Author: Matt
//
// ------------------------------------------------------------------------------
#include "Argyle.h"
#include "Platform/GraphicsInterface.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#define RENDERER_DLL "GLRenderer.dll"

namespace argyle::core
{

void test_gl_renderer()
{
    // Load dll
    HMODULE                               hmod                   = LoadLibraryA(RENDERER_DLL);
    graphics::get_graphics_interface_func get_graphics_interface = nullptr;
    if (hmod)
    {
        get_graphics_interface = (graphics::get_graphics_interface_func) GetProcAddress(hmod, "get_graphics_interface");

        graphics::graphics_interface gfx_interface;
        // graphics::get_graphics_interface(gfx_interface);
        if (get_graphics_interface)
        {
            get_graphics_interface(gfx_interface);
        }
        gfx_interface.initialize();
        gfx_interface.test_run();
        gfx_interface.shutdown();

        FreeLibrary(hmod);
    }
}

} // namespace argyle::core