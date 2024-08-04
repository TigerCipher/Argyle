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
// File Name: UUID.h
// Date File Created: 08/02/2024
// Author: Matt
//
// ------------------------------------------------------------------------------

#pragma once
#include "Types.h"

#include <string>


namespace argyle::utl::uuid
{

// Generate a new UUID
u32 generate();

// Generate a new UUID and store it in the UUID manager
u32 generate_and_store(const std::string& name = "");

// Store a UUID in the UUID manager along with the name of the object
void store(u32 id, const std::string& name = "");

// Check if a UUID is stored in the UUID manager
bool is_stored(u32 id);

// Remove a UUID from the UUID manager
void remove(u32 id);

// Clear all UUIDs from the UUID manager
void clear();

// Get the name of a UUID
std::string get_name(u32 id);

// Save the UUID manager to a file
void save(const std::string& file_name);

// Load the UUID manager from a file
void load(const std::string& file_name);

} // namespace argyle::utl::uuid
