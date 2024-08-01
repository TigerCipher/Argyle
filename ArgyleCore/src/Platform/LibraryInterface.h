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
// File Name: LibraryInterface.h
// Date File Created: 08/01/2024
// Author: Matt
//
// ------------------------------------------------------------------------------

#pragma once

namespace argyle::platform
{
struct library_interface
{
    void* (*load_library)(const char* library_name);
    void  (*unload_library)(void* library_handle);
    void* (*get_function)(void* library_handle, const char* function_name);
};

const library_interface& get_library_interface();

} // namespace argyle::platform