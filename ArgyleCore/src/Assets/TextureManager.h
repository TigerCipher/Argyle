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
#pragma once

#include "Common.h"
#include "Graphics/Texture.h"

namespace argyle::assets
{

class texture_manager
{
public:
    texture_manager()  = default;
    ~texture_manager() = default;

    bool load_texture(const std::string& name, const std::string& path, bool flip = true);
    void unload_texture(const std::string& name);
    void unload_all_textures();

    graphics::texture* operator[](const std::string& name) const;

    bool texture_exists(const std::string& name) const;

    constexpr const std::unordered_map<std::string, graphics::texture*>& get_textures() const { return m_textures; }

private:
    std::unordered_map<std::string, graphics::texture*> m_textures;
};

extern texture_manager g_textures;

} // namespace argyle::assets
