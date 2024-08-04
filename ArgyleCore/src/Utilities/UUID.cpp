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
// File Name: UUID
// Date File Created: 08/02/2024
// Author: Matt
//
// ------------------------------------------------------------------------------
#include "UUID.h"

#include "Logger.h"

#include <unordered_map>
#include <fstream>

namespace argyle::utl::uuid
{

namespace
{
// Data structure to manage the UUIDs along with their names
std::unordered_map<u32, std::string> uuids;
} // anonymous namespace

// Generate a new UUID
u32 generate()
{
    return (u32) string_hash{}(std::to_string(std::rand()));
}

// Generate a new UUID and store it in the UUID manager
u32 generate_and_store(const std::string& name)
{
    const u32 id = generate();
    store(id, name);
    return id;
}

// Store a UUID in the UUID manager along with the name of the object
void store(u32 id, const std::string& name)
{
    if(is_stored(id))
    {
        LOG_WARN("UUID {} already stored with name: {}", id, get_name(id));
        return;
    }
    uuids[id] = name;
}

// Check if a UUID is stored in the UUID manager
bool is_stored(u32 id)
{
    return !uuids.empty() && uuids.contains(id);
}

// Remove a UUID from the UUID manager
void remove(u32 id)
{
    uuids.erase(id);
}

// Clear all UUIDs from the UUID manager
void clear()
{
    uuids.clear();
}

// Get the name of a UUID
std::string get_name(u32 id)
{
    return uuids[id];
}

// Save the UUID manager to a file
void save(const std::string& file_name)
{
    std::ofstream file(file_name);
    if (file.is_open())
    {
        for (const auto& [id, name] : uuids)
        {
            file << id << " " << name << '\n';
        }
    }
    else
    {
        LOG_ERROR("Failed to open file: {}", file_name);
    }
}

// Load the UUID manager from a file
void load(const std::string& file_name)
{
    std::ifstream file(file_name);
    if (file.is_open())
    {
        u32 id;
        std::string name;
        while (file >> id >> name)
        {
            store(id, name);
        }
    }
    else
    {
        LOG_ERROR("Failed to open file: {}", file_name);
    }

}

} // namespace argyle::utl::uuid