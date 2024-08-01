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
// File Name: Modules
// Date File Created: 08/01/2024
// Author: Matt
//
// ------------------------------------------------------------------------------

#include "Modules.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

namespace argyle::core
{

namespace
{
graphics::graphics_interface gfx_interface;
HMODULE rendererModule = nullptr;
} // anonymous namespace

const graphics::graphics_interface& graphics_interface()
{
    return gfx_interface;
}

bool load_renderer(const char* dll_name)
{
    // Load dll
    rendererModule = LoadLibraryA(dll_name);

    if (rendererModule)
    {
        graphics::get_graphics_interface_func get_graphics_interface = nullptr;
        get_graphics_interface = reinterpret_cast<graphics::get_graphics_interface_func>(GetProcAddress(rendererModule, "get_graphics_interface"));

        if (get_graphics_interface)
        {
            get_graphics_interface(gfx_interface);
        }
        return true;
    }
    return false;
}

void unload_renderer()
{
    if (rendererModule)
    {
        FreeLibrary(rendererModule);
    }
}


} // namespace argyle::core