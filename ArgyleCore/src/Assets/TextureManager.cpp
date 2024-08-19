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
// File Name: TextureManager
// Date File Created: 08/18/2024
// Author: Matt
//
// ------------------------------------------------------------------------------
#include "TextureManager.h"

#include <ranges>

namespace argyle::assets
{
texture_manager g_textures;

bool texture_manager::load_texture(u16 key, const std::string& path, bool flip)
{
    graphics::texture* texture = new graphics::texture();
    if (!texture->load(path, flip))
    {
        delete texture;
        return false;
    }

    m_textures[key] = texture;
    return true;
}

void texture_manager::unload_texture(u16 key)
{
    if (const auto it = m_textures.find(key); it != m_textures.end())
    {
        delete it->second;
        m_textures.erase(it);
    }
}

void texture_manager::unload_all_textures()
{
    for (const auto& texture : m_textures | std::views::values)
    {
        delete texture;
    }
    m_textures.clear();
}


graphics::texture* texture_manager::operator[](u16 key) const
{
    return m_textures.at(key);
}

bool texture_manager::texture_exists(u16 key) const
{
    return m_textures.contains(key);
}

} // namespace argyle::assets