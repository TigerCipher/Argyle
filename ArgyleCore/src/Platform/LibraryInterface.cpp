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
// File Name: LibraryInterface
// Date File Created: 08/01/2024
// Author: Matt
//
// ------------------------------------------------------------------------------

#include "LibraryInterface.h"

#ifdef _WIN32
    #define WIN32_LEAN_AND_MEAN
    #include <Windows.h>
// UNTESTED
#elif defined(__linux__)
    #include <dlfcn.h>
#endif

namespace argyle::platform
{

namespace
{
library_interface lib_interface;
} // anonymous namespace

const library_interface& get_library_interface()
{
    if (lib_interface.load_library && lib_interface.unload_library && lib_interface.get_function)
    {
        return lib_interface;
    }

// Windows implementation
#ifdef _WIN32
    lib_interface.load_library   = [](const char* library_name) -> void* { return LoadLibraryA(library_name); };
    lib_interface.unload_library = [](void* library_handle) { FreeLibrary(static_cast<HMODULE>(library_handle)); };
    lib_interface.get_function   = [](void* library_handle, const char* function_name) -> void* {
        return GetProcAddress(static_cast<HMODULE>(library_handle), function_name);
    };
    // UNTESTED
#elif defined(__linux__)
    lib_interface.load_library   = [](const char* library_name) -> void* { return dlopen(library_name, RTLD_LAZY); };
    lib_interface.unload_library = [](void* library_handle) { dlclose(library_handle); };
    lib_interface.get_function   = [](void* library_handle, const char* function_name) -> void* {
        return dlsym(library_handle, function_name);
    };
#endif

    return lib_interface;
}

} // namespace argyle::platform