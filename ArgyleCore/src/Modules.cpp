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
#include "Platform/LibraryInterface.h"

namespace argyle::core
{

namespace
{
graphics::graphics_interface gfx_interface;
void*                        renderer_module = nullptr;
} // anonymous namespace

const graphics::graphics_interface& graphics_interface()
{
    return gfx_interface;
}


// TODO: Need this to be platform independent
bool load_renderer(const char* dll_name)
{
    // Load dll
    renderer_module = platform::get_library_interface().load_library(dll_name);

    if (renderer_module)
    {
        if (const auto get_graphics_interface =
                reinterpret_cast<graphics::get_graphics_interface_func>(
                    platform::get_library_interface().get_function(renderer_module, "get_graphics_interface")))
        {
            get_graphics_interface(gfx_interface);
        }
        return true;
    }
    return false;
}

void unload_renderer()
{
    if (renderer_module)
    {
        platform::get_library_interface().unload_library(renderer_module);
    }
}


} // namespace argyle::core